#ifndef ATA_EVENT_H
#define ATA_EVENT_H
#include "ATA/config.h"
#include <functional>

namespace ata
{
    template<typename ... Args>
    class Event
    {
        private:
		
            std::function<void(Args...)> m_handler;

        public:
		
            template<typename Callback>
            void connect(Callback&& cb)
            {
                m_handler = cb;
            }

            template<typename ... A>
            void emit(A&& ... args)
            {
                if(m_handler)
                {
                    m_handler(std::forward<A>(args)...);
                }
            }
			
    };

    extern ATA_API void pollEvents();
	
    extern ATA_API void waitEvents();
	
    extern ATA_API void waitEvents(double timeout);
	
    extern ATA_API void postEmptyEvent();
}

#endif
