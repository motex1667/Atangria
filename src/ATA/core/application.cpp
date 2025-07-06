#include "ATA/core/application.h"
#include "ATA/core/surface.h"
#include "ATA/state/controller.h"

namespace ata
{
    Application::Application(ata::WindowConfig config) :
        m_controller(config)
    {
    }

    Application::~Application()
    {
    }
}
