#ifndef ATA_MEMORY_INPUT_STREAM_H
#define ATA_MEMORY_INPUT_STREAM_H
#include "ATA/config.h"
#include "ATA/utils/input_stream.h"
#include <cstdlib>


namespace ata
{
	class ATA_API MemoryInputStream : public InputStream
	{
		public:

			MemoryInputStream();

			void open(const void* data, size_t sizeInBytes);

			virtual SPint64 read(void* data, SPint64 size);

			virtual SPint64 seek(SPint64 position);

			virtual SPint64 tell();

			virtual SPint64 getSize();

		private:

			const char* m_data;
			SPint64     m_size;
			SPint64     m_offset;
	};
}

#endif