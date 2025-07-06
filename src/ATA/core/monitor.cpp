#include "ATA/config/glfw_3_3.h"
#include "ATA/core/monitor.h"

namespace ata
{
    Event<Monitor, MonitorEventType> monitorEvent {};
    Monitor::Monitor(void* handle)
    {
        m_handle = handle;
    }

    Monitor::operator void*() const
    {
        return m_handle;
    }

    std::vector<Monitor> Monitor::getMonitors()
    {
        int count;
        auto pMonitors = glfwGetMonitors(&count);

        std::vector<Monitor> monitors;
        monitors.reserve(count);
        for(int i = 0; i < count; ++i)
        {
            monitors.emplace_back(pMonitors[i]);
        }
        return monitors;
    }

    Monitor getPrimaryMonitor()
    {
        return Monitor{glfwGetPrimaryMonitor()};
    }

    ata::vec2i Monitor::getPosition() const
    {
        int x, y;
        glfwGetMonitorPos(static_cast<GLFWmonitor*>(m_handle), &x, &y);
        return ata::vec2i(x, y);
    }
	
    ata::vec2f Monitor::getContentScale() const
    {
        float x, y;
        glfwGetMonitorContentScale(static_cast<GLFWmonitor*>(m_handle), &x, &y);
        return ata::vec2f(x, y);
    }

    const char* Monitor::getName() const
    {
        return glfwGetMonitorName(static_cast<GLFWmonitor*>(m_handle));
    }


    void Monitor::setUserPointer(void* ptr_)
    {
        glfwSetMonitorUserPointer(static_cast<GLFWmonitor*>(m_handle), ptr_);
    }

    void* Monitor::getUserPointer() const
    {
        return glfwGetMonitorUserPointer(static_cast<GLFWmonitor*>(m_handle));
    }

    std::vector<VideoMode> Monitor::getVideoModes() const
    {
        int count;
        auto pModes = glfwGetVideoModes(static_cast<GLFWmonitor*>(m_handle), &count);

        std::vector<VideoMode> modes;
        modes.reserve(count);
        for(int i = 0; i < count; ++i)
        {
            modes.push_back(pModes[i]);
        }
        return modes;
    }

    VideoMode Monitor::getVideoMode() const
    {
        return *glfwGetVideoMode(static_cast<GLFWmonitor*>(m_handle));
    }

    void Monitor::setGamma(float gamma)
    {
        glfwSetGamma(static_cast<GLFWmonitor*>(m_handle), gamma);
    }

    GammaRamp Monitor::getGammaRamp() const
    {
        return *glfwGetGammaRamp(static_cast<GLFWmonitor*>(m_handle));
    }

    void Monitor::setGammaRamp(const GammaRamp& ramp)
    {
        glfwSetGammaRamp(static_cast<GLFWmonitor*>(m_handle), &ramp);
    }
}
