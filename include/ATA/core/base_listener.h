#ifndef ATA_BASE_LISTENER_H
#define ATA_BASE_LISTENER_H
#include "ATA/core/apidefs.h"
#include <vector>

namespace ata
{
    class Surface;
	
    class ATA_API BaseListener
    {
        protected:
		
            BaseListener(){}

        public:
		
            virtual ~BaseListener()
			{
			}
			
            virtual void onKey(KeyCode keycode, int scancode, KeyState keystate, ModifierKeyBit keymodifier)
			{
			}
			
            virtual void onChar(unsigned int codepoint)
			{
			}
			
            virtual void onMouseButton(MouseButton mouseButton, MouseButtonState buttonState, ModifierKeyBit keyModifier)
			{				
			}
			
            virtual void onCursorPos(double xPos, double yPos)
			{
			}
			
            virtual void onCursorEnter(bool enter)
			{
			}
			
            virtual void onScroll(double xOffset, double yOffset)
			{
			}
			
            virtual void onDropPath(std::vector<const char*> paths)
			{
			}
			
            virtual void onWindowPos(int xPos, int yPos)
			{
			}
			
            virtual void onWindowSize(int width, int height)
			{
			}
			
            virtual void onWindowClose()
			{
			}
			
            virtual void onWindowRefresh()
			{
			}
			
            virtual void onWindowFocus(bool focusGain)
			{
			}
			
            virtual void onWindowIconify(bool iconified)
			{
			}
			
            virtual void onWindowMaximize(bool maximized)
			{
			}
			
            virtual void onWindowFramebufferSize(int width, int height)
			{
			}
			
            virtual void onWindowContentScale(float xScale, float yScale)
			{
			}
			
    };
}

#endif