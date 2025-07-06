#include "ATA/config/glfw_3_3.h"
#include "ATA/core/event.h"

namespace ata
{
    void pollEvents()
    {
        glfwPollEvents();
    }

    void waitEvents()
    {
        glfwWaitEvents();
    }

    void waitEvents(double timeout)
    {
        glfwWaitEventsTimeout(timeout);
    }

    void postEmptyEvent()
    {
        glfwPostEmptyEvent();
    }
}
