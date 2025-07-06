#ifndef ATA_INPUT_STREAM_H
#define ATA_INPUT_STREAM_H

namespace ata
{
	class ATA_API InputStream
	{
		public:
			
			virtual ~InputStream()
			{
			}
			
			virtual SPint64 read(void* data, SPint64) = 0;
			
			virtual SPint64 seek(SPint64 position) = 0;
			
			virtual SPint64 tell() = 0;
			
			virtual SPint64 getSize() = 0;
			
	};
}

#endif