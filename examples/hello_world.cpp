#include "ATA/core/surface.h"
#include "ATA/core/event.h"
#include <iostream>

int main(int argc, char** argv)
{
	ata::Surface surface;
	surface.create();

	while(surface.isRunning())
	{
		ata::pollEvents();
		surface.swapBuffers();
	}
	return 0;
}