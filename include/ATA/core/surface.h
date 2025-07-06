#ifndef ATA_SURFACE_H
#define ATA_SURFACE_H
#include "ATA/config.h"
#include "ATA/core/apidefs.h"
#include "ATA/core/event.h"
#include "ATA/core/no_copy.h"
#include "ATA/core/no_move.h"
#include "ATA/core/context.h"
#include "ATA/math/vec.h"
#include "ATA/math/rect.h"
#include "ATA/gfx/color.h"
#include <vector>

typedef struct GLFWwindow GLFWwindow;
namespace ata
{
    class ATA_API Surface final : public NonCopyable /*, public Renderer*/
    {
        public:
            Event<Surface*, KeyCode, int, KeyState, ModifierKeyBit> keyEvent;
            Event<Surface*, unsigned int> charEvent;
            Event<Surface*, MouseButton, MouseButtonState, ModifierKeyBit> mouseButtonEvent;
            Event<Surface*, double, double> cursorPosEvent;
            Event<Surface*, bool> cursorEnterEvent;
            Event<Surface*, double, double> scrollEvent;
            Event<Surface*, std::vector<const char*>> dropEvent;
            Event<Surface*, int, int> posEvent;
            Event<Surface*, int, int> sizeEvent;
            Event<Surface*> closeEvent;
            Event<Surface*> refreshEvent;
            Event<Surface*, bool> focusEvent;
            Event<Surface*, bool> iconifyEvent;
            Event<Surface*, bool> maximizeEvent;
            Event<Surface*, int, int> framebufferSizeEvent;
            Event<Surface*, float, float> contentScaleEvent;

            explicit Surface();
			
           ~Surface();

            bool create(WindowConfig conf = {});

            void setAspectRatio(int x, int y);
			
            void setAspectRatio(const vec2i& aspectRatio);
			
            void setAutoIconify(bool autoIconify);
			
            void setClipboardString(const char* str);
			
            void setCursorImage(const unsigned char* data, unsigned width, unsigned height, int x = 0, int y = 0);
			
            void setCursorPosition(int x, int y);
			
            void setCursorPosition(const vec2i& pos);
			
            void setCursorMode(CursorMode cursorMode);
			
            void setDecorated(bool decorated);
			
            void setFocusOnShow(bool focus);
			
            void setIcon(const unsigned char* pixels, unsigned width, unsigned height);
			
            void setOpacity(float opacity);
			
            void setPosition(int x, int y);
			
            void setPosition(const vec2i& pos);
			
            void setResizable(bool resizable);
			
            void setTitle(const char* title);
			
            void setTopmost(bool topmost);
			
            void setSize(unsigned width, unsigned height);
			
            void setSize(const vec2u& dim);
			
            void setSizeLimits(int minW, int minH, int maxW, int maxH);
			
            void setSizeLimits(const recti& dim);
			
            void setVisible(bool visible);
			
            void setFullscreen(bool toggle);
			
            void setUserPointer(void* user);

            bool isAutoIconified() const;
			
            vec2i getAspectRatio() const;
			
            const char* getClipboardString() const;
			
            vec2f getContentScale() const;
			
            vec2i getCursorPosition() const;
			
            CursorMode getCursorMode() const;
			
            vec2u getFramebufferSize() const;
			
            bool isDecorated() const;
			
            bool isFocusedOnShow() const;
			
            float getOpacity() const;
			
            vec2i getPosition() const;
			
            bool isResizable() const;
			
            const char* getTitle() const;
			
            bool isTopmost() const;
			
            vec2u getSize() const;
			
            recti getSizeLimits() const;
			
            bool isVisible() const;
			
            bool isFullscreen() const;
			
            bool hasFocus() const;
			
            bool isMouseInside() const;
			
            bool isRunning() const;
			
            bool isIconified() const;
			
            bool isMaximized() const;
			
            void* getUserPointer();
			
            void close();
			
            void iconify();
			
            void maximize();
			
            void restore();
			
            void focus();
			
            void swapBuffers();
			
            bool makeContextCurrent(bool set);
			
            bool isContextCurrent() const;
			
			static bool rawMouseMotionSupported();
			
			static double getTime();
			
            static void setTime(double time);
			
            static SPuint64 getTimerValue();
			
            static SPuint64 getTimerFrequency();

        private:
		
            friend void keyCallback(GLFWwindow* window, int key, int scanCode, int state, int mods);
			
            friend void charCallback(GLFWwindow* window, unsigned int codepoint);
			
            friend void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);
			
            friend void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
			
            friend void cursorEnterCallback(GLFWwindow* window, int value);
			
            friend void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
			
            friend void dropCallback(GLFWwindow* window, int count, const char** pPaths);
			
            friend void sizeCallback(GLFWwindow* window, int width, int height);
			
            friend void closeCallback(GLFWwindow* window);
			
            friend void posCallback(GLFWwindow* window, int xPos, int yPos);
			
            friend void focusCallback(GLFWwindow* window, int value);
			
            friend void iconifyCallback(GLFWwindow* window, int value);
			
            friend void maximizeCallback(GLFWwindow* window, int value);
			
            friend void framebufferSizeCallback(GLFWwindow* window, int width, int height);
			
            friend void contentScaleCallback(GLFWwindow* window, float xScale, float yScale);
		
		private:
            void* m_monitor;
            void* m_user_pointer;
            bool m_quit;
            bool m_focused;
            bool m_focus_on_show;
            bool m_iconified;
            bool m_auto_iconify;
            bool m_maximized;
            bool m_visible;
            bool m_resizable;
            bool m_topmost;
            bool m_decorated;
            bool m_cursor_enter;
            bool m_fullscreen;
            float m_opacity;
            const char* m_title;
            CursorMode m_cursor_mode;
            rectu m_window_dim_save;
            recti m_window_size_limits;
            vec2i m_aspect_ratio;
            vec2f m_content_scale;
            vec2i m_cursor_pos;
            vec2u m_window_size;
            vec2u m_framebuffer_size;
            vec2i m_window_pos;
            GraphicsContext* m_context;
			
    };
}

#endif
