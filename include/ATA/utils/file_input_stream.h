#ifndef ATA_FILE_INPUT_STREAM_H
#define ATA_FILE_INPUT_STREAM_H
#include "ATA/config.h"
#include "ATA/utils/input_stream.h"
#include "ATA/core/no_copy.h"
#include <stdio.h>
#include <string>

namespace ata
{
	class ATA_API FileInputStream : public InputStream, NonCopyable
	{
		public:
			
			FileInputStream();
			
			virtual ~FileInputStream();
			
			bool open(const std::string& filename);
			
			virtual SPint64 read(void* data, SPint64 size);
			
			virtual SPint64 seek(SPint64 position);
			
			virtual SPint64 tell();
			
			virtual SPint64 getSize();
			
		private:
		
			FILE* m_file;
			
	};
}

#endif