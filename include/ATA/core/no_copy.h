#ifndef ATA_NO_COPY_H
#define ATA_NO_COPY_H

namespace ata
{
    class NonCopyable
    {
        public:
		
            NonCopyable()
			{
			}
			
           ~NonCopyable()
			{
			}
		   
            NonCopyable(const NonCopyable&) = delete;
			
            NonCopyable& operator=(const NonCopyable&) = delete;
			
    };
}

#endif
