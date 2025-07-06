#ifndef ATA_THREAD_H
#define ATA_THREAD_H
#include "ATA/config.h"
#include "ATA/run/cthread.h"
#include "ATA/core/no_copy.h"

namespace ata
{
    namespace detail
    {
        class MutexImpl;
        class ThreadLocalImpl;
        class ThreadImpl;
        struct ThreadFunctor;
    }

    class ATA_API Thread : public NonCopyable
    {
        public:
            template<typename F>
            Thread(F f);

            template<typename F, typename A>
            Thread(F f, A a);

            template<typename C>
            Thread(void(C::*f)(), C* cls);

           ~Thread();

            void launch();
            void wait();
            void terminate();

        private:
            friend class detail::ThreadImpl;
            void run();

            detail::ThreadImpl* m_thread_impl;
            detail::ThreadFunctor* m_entry_point;
    };
	
#include "ATA/run/thread.inl"

}
#endif
