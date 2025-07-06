#ifndef ATA_APPLICATION_H
#define ATA_APPLICATION_H
#include "ATA/core/apidefs.h"
#include "ATA/core/no_copy.h"
#include "ATA/core/no_move.h"
#include "ATA/utils/timer.h"
#include "ATA/state/default_segue.h"
#include "ATA/state/default_frame.h"
#include "ATA/state/controller.h"
#include "ATA/gfx/renderer.h"

namespace ata
{
    class Surface;
    class DefaultSegue;
	
    class ATA_API Application : public NonCopyable, NonMovable
    {
        public:
		
            Application(WindowConfig = {});
			
           ~Application();

            template<typename M = DefaultFrame, typename S = DefaultSegue, typename D = time::seconds<0>, typename ... Args>
            int run(Args&& ... args);

        private:
		
            Controller m_controller;
			
    };

#include "ATA/core/application.inl"

}

#endif
