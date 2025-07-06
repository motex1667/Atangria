#ifndef ATA_MONITOR_H
#define ATA_MONITOR_H
#include "ATA/config.h"
#include "ATA/core/event.h"
#include "ATA/math/rect.h"
#include "ATA/math/vec.h"
#include <vector>

namespace ata
{
    typedef GLFWvidmode VideoMode;
    typedef GLFWgammaramp GammaRamp;
	
    class ATA_API Monitor
    {
        private:
		
            void* m_handle;

        public:
		
            friend class Surface;
            friend class GraphicsContext;

            explicit Monitor(void* handle = nullptr);

            Monitor(const Monitor&) = default;
			
            Monitor& operator=(const Monitor&) = default;

            Monitor(Monitor&&) = default;
			
            Monitor& operator=(Monitor&&) = default;

            operator void*() const;

            static std::vector<Monitor> getMonitors();

            vec2i getPosition() const;
			
            recti getWorkArea() const;

            vec2i getPhysicalSize() const;
			
            vec2f getContentScale() const;
			
            void setUserPointer(void* ptr);
			
            void* getUserPointer() const;
			
            const char* getName() const;
			
            std::vector<VideoMode> getVideoModes() const;
			
            VideoMode getVideoMode() const;

            void setGamma(float gamma);
			
            GammaRamp getGammaRamp() const;
			
            void setGammaRamp(const GammaRamp& ramp);
			
    };

    inline std::vector<Monitor> getMonitors();
	
    inline Monitor getPrimaryMonitor();

    enum class MonitorEventType : int
    {
        Connected = GLFW_CONNECTED,
        Disconnected = GLFW_DISCONNECTED
    };
	
    extern Event<Monitor, MonitorEventType> monitorEvent;
}

#endif
