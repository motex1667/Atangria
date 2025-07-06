#ifndef ATA_GLRESOURCE
#define ATA_GLRESOURCE

namespace ata
{
    class GLResource
    {
        protected:

            GLResource();

           ~GLResource();
			
			class ContextLock
			{
				/*
				 *  behavior:
				 *  - context locks only work if there had been a GL-object before that instantiated the shared context
				 *  - 
				 *
				 *  - whenever there is a GC active, create objects by that GC
				 *  - if no GC is active, then create objects by SC
				 *  - if SC has not been created, then create SC and create objects by it
				 *
				 *  - if GC was previously active, then do nothing
				 *  - if no GC was previously active, then SC was used (potentially even been created by this)
				 *  - if SC was created by this, then destroy SC
				 *
				 *  step 1:
				 *  - check if there is an active GC, if yes, then do nothing
				 *
				 *  step 2:
				 *  - no active gc -> is sc created, if yes, then make it current, otherwise create it
				 *
				 *  step 3:
				 *  - object creation (increments reference count)
				 *
				 *  step 4:
				 *
				 */
				public:
				
					ContextLock();
					
				   ~ContextLock();

			};
    };	
}
#endif