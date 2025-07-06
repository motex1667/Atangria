#ifndef ATA_NO_MOVE_H
#define ATA_NO_MOVE_H

namespace ata
{
    class NonMovable
    {
        public:
		
            NonMovable()
			{
			}
			
           ~NonMovable()
			{
			}
			
            NonMovable(NonCopyable&&) = delete;
			
            NonMovable& operator=(NonCopyable&&) = delete;
			
    };
}

#endif
