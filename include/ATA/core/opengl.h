#ifndef ATA_OPENGL_H
#define ATA_OPENGL_H

#include "ATA/config.h"
#if defined(ATA_PLATFORM_WINDOWS) || defined(ATA_PLATFORM_LINUX)
	#if defined(ATA_PLATFORM_WINDOWS) && defined(_MSC_VER)
		#include <windows.h>
	#endif
	#include <GL/gl.h>
#elif defined(ATA_PLATFORM_MACOS)
	#include <OpenGL/gl.h>
#endif

#endif