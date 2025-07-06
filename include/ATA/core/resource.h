#ifndef ATA_RESOURCE_H
#define ATA_RESOURCE_H
#include "ATA/config.h"
#include <string>

namespace ata
{
	class InputStream;
	class Resource
	{
		public:
		
			virtual ~Resource() = default;
			
			virtual bool loadFromFile(const std::string& filename) { return false; }
			
			virtual bool loadFromMemory(const void* data, size_t size) { return false; }
			
			virtual bool loadFromStream(InputStream& stream) { return false; }
			
			virtual bool saveToFile(const std::string& filename) const { return false; }
			
		protected:
			Resource() = default;
	};
}

#endif