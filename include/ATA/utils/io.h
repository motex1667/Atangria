#ifndef ATA_IO_H
#define ATA_IO_H
#include "ATA/config.h"
#include <string>

namespace ata
{
    ATA_DEPRECATED ATA_API SPubyte* loadImage(const std::string& path,
                    int& width,
                    int& height,
                    int& channels,
                    int requested);
    ATA_API SPubyte* loadData(const std::string& path);
    ATA_API SPubyte* loadData(const std::string& path, size_t& fileSize);
	ATA_API bool writeData(const std::string& output, SPsize count, const SPubyte* data);
    ATA_API void freeResource(const void* res);
}

#endif // SIMPLE_RESOURCE_LOADER_H
