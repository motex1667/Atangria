#ifndef ATA_TIMER_H
#define ATA_TIMER_H
#include "ATA/config.h"
#include "ATA/run/thread.h"
#include "ATA/core/no_copy.h"
#include <map>
#include <vector>
#include <functional>
#include <atomic>

namespace ata
{
    ATA_API extern double asSeconds(SPuint64 base);
    ATA_API extern SPuint32 asMilliseconds(SPuint64 base);
    ATA_API extern SPuint64 asMicroseconds(SPuint64 base);

    ATA_API extern SPuint64 seconds(double sec);
    ATA_API extern SPuint64 milliseconds(SPuint32 mil);
    ATA_API extern SPuint64 microseconds(SPuint64 mic);

    class ATA_API StopWatch
    {
        public:
            StopWatch();

            SPuint64 getElapsed();
            SPuint64 reset();
			
        private:
            SPuint64 m_initial; //core value in microseconds..
    };
	
	class ATA_API Task 
	{
		public:
			friend class Timer;
			Task(const std::function<void(SPtime)>& func);
			~Task();

			void withDuration(SPtime time);
		private:
			SPint32 m_duration;
			std::function<void(SPtime)> m_function;
	};
			
	class ATA_API Trigger
	{
		public:
			friend class Timer;
			
			Trigger();
		   ~Trigger();
			Task& doTask(const std::function<void(SPtime)>& task);
			
		private:
			std::vector<Task> m_tasks;
	};
			
	class ATA_API Timer 
	{
		public:
			
			Timer();
			Timer(const Timer& rhs);
		   ~Timer();
		   
			void reset();
			void start();
			void pause();
			bool isPaused() const;
			bool isReversed() const;
			SPtime getElapsed() const;
			void update(const SPtime& span);
			Trigger& at(const SPtime& time);
			void clear();
			void reverse(bool state);
			void set(const SPtime& time);
			
		private:
			SPint32 m_elapsed;
			bool m_paused;
			bool m_reversed;
			std::map<SPint32, Trigger> m_triggers;
	};
	
	class ATA_API EventTimer : public NonCopyable
	{
		public:
			EventTimer();
		   ~EventTimer();
			
			void setPreAction(std::function<void()> fn);
			void setPostAction(std::function<void()> fn);
			void setTrigger(double stamp, std::function<void(SPtime)> fn, double duration = 0.0);
			void setDuration(double duration);
			
			void reset();
			void start();
			void stop();
			void clear();
			
			bool isRunning() const;
			
		private:
			static void process(EventTimer* timer);
			
			void execPreAction();
			void execPostAction();
			
			Timer& getTimer();
			
			std::atomic<bool> m_running{false};
			std::function<void()> m_pre_action;
			std::function<void()> m_post_action;
			
			double m_duration;
			Timer m_timer;
			ata::Thread m_thread;
	};
	
    namespace time
    {
        template<int val = 0>
        struct seconds
        {
            static SPtime value() { return ata::seconds(val); }
        };

        template<SPuint32 val = 0>
        struct milliseconds
        {
            static SPtime value() { return ata::milliseconds(val); }
        };

        template<SPuint64 val = 0>
        struct microseconds
        {
            static SPtime value() { return ata::microseconds(val); }
        };

        template<int val = 0>
        using sec = seconds<val>;

        template<SPuint32 val = 0>
        using milli = milliseconds<val>;

        template<SPuint64 val = 0>
        using micro = microseconds<val>;
    }
}

#endif // TIMER_H
