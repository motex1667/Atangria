#include "ATA/config/glfw_3_3.h"
#include "ATA/core/surface.h"
#include "ATA/core/monitor.h"
#include "ATA/core/log.h"

namespace
{
	inline int translateCursorMode(ata::CursorMode mode)
	{
		switch(mode)
		{
			case ata::CursorMode::Disabled: return GLFW_CURSOR_DISABLED;
			case ata::CursorMode::Hidden: return GLFW_CURSOR_HIDDEN;
			default: break;
		}
		return GLFW_CURSOR_NORMAL;
	}
	
	inline ata::KeyCode translateKeyCode(int code)
	{
		switch(code)
		{
			case GLFW_KEY_SPACE: return ata::KeyCode::Space;
			case GLFW_KEY_APOSTROPHE: return ata::KeyCode::Apostrophe;
			case GLFW_KEY_COMMA: return ata::KeyCode::Comma;
			case GLFW_KEY_MINUS: return ata::KeyCode::Minus;
			case GLFW_KEY_PERIOD: return ata::KeyCode::Period;
			case GLFW_KEY_SLASH: return ata::KeyCode::Slash;
			case GLFW_KEY_0: return ata::KeyCode::Zero;
			case GLFW_KEY_1: return ata::KeyCode::One;
			case GLFW_KEY_2: return ata::KeyCode::Two;
			case GLFW_KEY_3: return ata::KeyCode::Three;
			case GLFW_KEY_4: return ata::KeyCode::Four;
			case GLFW_KEY_5: return ata::KeyCode::Five;
			case GLFW_KEY_6: return ata::KeyCode::Six;
			case GLFW_KEY_7: return ata::KeyCode::Seven;
			case GLFW_KEY_8: return ata::KeyCode::Eight;
			case GLFW_KEY_9: return ata::KeyCode::Nine;
			case GLFW_KEY_SEMICOLON: return ata::KeyCode::Semicolon;
			case GLFW_KEY_EQUAL: return ata::KeyCode::Equal;
			case GLFW_KEY_A: return ata::KeyCode::A;
			case GLFW_KEY_B: return ata::KeyCode::B;
			case GLFW_KEY_C: return ata::KeyCode::C;
			case GLFW_KEY_D: return ata::KeyCode::D;
			case GLFW_KEY_E: return ata::KeyCode::E;
			case GLFW_KEY_F: return ata::KeyCode::F;
			case GLFW_KEY_G: return ata::KeyCode::G;
			case GLFW_KEY_H: return ata::KeyCode::H;
			case GLFW_KEY_I: return ata::KeyCode::I;
			case GLFW_KEY_J: return ata::KeyCode::J;
			case GLFW_KEY_K: return ata::KeyCode::K;
			case GLFW_KEY_L: return ata::KeyCode::L;
			case GLFW_KEY_M: return ata::KeyCode::M;
			case GLFW_KEY_N: return ata::KeyCode::N;
			case GLFW_KEY_O: return ata::KeyCode::O;
			case GLFW_KEY_P: return ata::KeyCode::P;
			case GLFW_KEY_Q: return ata::KeyCode::Q;
			case GLFW_KEY_R: return ata::KeyCode::R;
			case GLFW_KEY_S: return ata::KeyCode::S;
			case GLFW_KEY_T: return ata::KeyCode::T;
			case GLFW_KEY_U: return ata::KeyCode::U;
			case GLFW_KEY_V: return ata::KeyCode::V;
			case GLFW_KEY_W: return ata::KeyCode::W;
			case GLFW_KEY_X: return ata::KeyCode::X;
			case GLFW_KEY_Y: return ata::KeyCode::Y;
			case GLFW_KEY_Z: return ata::KeyCode::Z;
			case GLFW_KEY_LEFT_BRACKET: return ata::KeyCode::LeftBracket;
			case GLFW_KEY_BACKSLASH: return ata::KeyCode::Backslash;
			case GLFW_KEY_RIGHT_BRACKET: return ata::KeyCode::RightBracket;
			case GLFW_KEY_GRAVE_ACCENT: return ata::KeyCode::GraveAccent;
			case GLFW_KEY_WORLD_1: return ata::KeyCode::World1;
			case GLFW_KEY_WORLD_2: return ata::KeyCode::World2;
			case GLFW_KEY_ESCAPE: return ata::KeyCode::Escape;
			case GLFW_KEY_ENTER: return ata::KeyCode::Enter;
			case GLFW_KEY_TAB: return ata::KeyCode::Tab;
			case GLFW_KEY_BACKSPACE: return ata::KeyCode::Backspace;
			case GLFW_KEY_INSERT: return ata::KeyCode::Insert;
			case GLFW_KEY_DELETE: return ata::KeyCode::Delete;
			case GLFW_KEY_RIGHT: return ata::KeyCode::Right;
			case GLFW_KEY_LEFT: return ata::KeyCode::Left;
			case GLFW_KEY_DOWN: return ata::KeyCode::Down;
			case GLFW_KEY_UP: return ata::KeyCode::Up;
			case GLFW_KEY_PAGE_UP: return ata::KeyCode::PageUp;
			case GLFW_KEY_PAGE_DOWN: return ata::KeyCode::PageDown;
			case GLFW_KEY_HOME: return ata::KeyCode::Home;
			case GLFW_KEY_END: return ata::KeyCode::End;
			case GLFW_KEY_CAPS_LOCK: return ata::KeyCode::CapsLock;
			case GLFW_KEY_SCROLL_LOCK: return ata::KeyCode::ScrollLock;
			case GLFW_KEY_NUM_LOCK: return ata::KeyCode::NumLock;
			case GLFW_KEY_PRINT_SCREEN: return ata::KeyCode::PrintScreen;
			case GLFW_KEY_PAUSE: return ata::KeyCode::Pause;
			case GLFW_KEY_F1: return ata::KeyCode::F1;
			case GLFW_KEY_F2: return ata::KeyCode::F2;
			case GLFW_KEY_F3: return ata::KeyCode::F3;
			case GLFW_KEY_F4: return ata::KeyCode::F4;
			case GLFW_KEY_F5: return ata::KeyCode::F5;
			case GLFW_KEY_F6: return ata::KeyCode::F6;
			case GLFW_KEY_F7: return ata::KeyCode::F7;
			case GLFW_KEY_F8: return ata::KeyCode::F8;
			case GLFW_KEY_F9: return ata::KeyCode::F9;
			case GLFW_KEY_F10: return ata::KeyCode::F10;
			case GLFW_KEY_F11: return ata::KeyCode::F11;
			case GLFW_KEY_F12: return ata::KeyCode::F12;
			case GLFW_KEY_F13: return ata::KeyCode::F13;
			case GLFW_KEY_F14: return ata::KeyCode::F14;
			case GLFW_KEY_F15: return ata::KeyCode::F15;
			case GLFW_KEY_F16: return ata::KeyCode::F16;
			case GLFW_KEY_F17: return ata::KeyCode::F17;
			case GLFW_KEY_F18: return ata::KeyCode::F18;
			case GLFW_KEY_F19: return ata::KeyCode::F19;
			case GLFW_KEY_F20: return ata::KeyCode::F20;
			case GLFW_KEY_F21: return ata::KeyCode::F21;
			case GLFW_KEY_F22: return ata::KeyCode::F22;
			case GLFW_KEY_F23: return ata::KeyCode::F23;
			case GLFW_KEY_F24: return ata::KeyCode::F24;
			case GLFW_KEY_F25: return ata::KeyCode::F25;
			case GLFW_KEY_KP_0: return ata::KeyCode::KeyPad0;
			case GLFW_KEY_KP_1: return ata::KeyCode::KeyPad1;
			case GLFW_KEY_KP_2: return ata::KeyCode::KeyPad2;
			case GLFW_KEY_KP_3: return ata::KeyCode::KeyPad3;
			case GLFW_KEY_KP_4: return ata::KeyCode::KeyPad4;
			case GLFW_KEY_KP_5: return ata::KeyCode::KeyPad5;
			case GLFW_KEY_KP_6: return ata::KeyCode::KeyPad6;
			case GLFW_KEY_KP_7: return ata::KeyCode::KeyPad7;
			case GLFW_KEY_KP_8: return ata::KeyCode::KeyPad8;
			case GLFW_KEY_KP_9: return ata::KeyCode::KeyPad9;
			case GLFW_KEY_KP_DECIMAL: return ata::KeyCode::KeyPadDecimal;
			case GLFW_KEY_KP_DIVIDE: return ata::KeyCode::KeyPadDivide;
			case GLFW_KEY_KP_MULTIPLY: return ata::KeyCode::KeyPadMultiply;
			case GLFW_KEY_KP_SUBTRACT: return ata::KeyCode::KeyPadSubtract;
			case GLFW_KEY_KP_ADD: return ata::KeyCode::KeyPadAdd;
			case GLFW_KEY_KP_ENTER: return ata::KeyCode::KeyPadEnter;
			case GLFW_KEY_KP_EQUAL: return ata::KeyCode::KeyPadEqual;
			case GLFW_KEY_LEFT_SHIFT: return ata::KeyCode::LeftShift;
			case GLFW_KEY_LEFT_CONTROL: return ata::KeyCode::LeftControl;
			case GLFW_KEY_LEFT_ALT: return ata::KeyCode::LeftAlt;
			case GLFW_KEY_LEFT_SUPER: return ata::KeyCode::LeftSuper;
			case GLFW_KEY_RIGHT_SHIFT: return ata::KeyCode::RightShift;
			case GLFW_KEY_RIGHT_CONTROL: return ata::KeyCode::RightControl;
			case GLFW_KEY_RIGHT_ALT: return ata::KeyCode::RightAlt;
			case GLFW_KEY_RIGHT_SUPER: return ata::KeyCode::RightSuper;
			case GLFW_KEY_MENU: return ata::KeyCode::Menu;
			default: break;
		}
		return ata::KeyCode::None;
	}
	
	inline ata::ModifierKeyBit translateModifierKeyBit(int mod)
	{
		switch(mod)
		{
			case GLFW_MOD_SHIFT: return ata::ModifierKeyBit::Shift;
			case GLFW_MOD_CONTROL: return ata::ModifierKeyBit::Control;
			case GLFW_MOD_ALT: return ata::ModifierKeyBit::Alt;
			case GLFW_MOD_SUPER: return ata::ModifierKeyBit::Super;
			case GLFW_MOD_CAPS_LOCK: return ata::ModifierKeyBit::CapsLock;
			case GLFW_MOD_NUM_LOCK: return ata::ModifierKeyBit::NumLock;
			default: break;
		}
		return ata::ModifierKeyBit::None;
	}
	
	inline ata::MouseButton translateMouseButton(int button)
	{
		if(button == GLFW_MOUSE_BUTTON_LAST)
			return ata::MouseButton::MaxValue;
		if(button == GLFW_MOUSE_BUTTON_LEFT)
			return ata::MouseButton::Left;
		if(button == GLFW_MOUSE_BUTTON_RIGHT) 
			return ata::MouseButton::Right;
		if(GLFW_MOUSE_BUTTON_MIDDLE) 
			return ata::MouseButton::Middle;
		
		switch(button)
		{
			case GLFW_MOUSE_BUTTON_1: return ata::MouseButton::One;
			case GLFW_MOUSE_BUTTON_2: return ata::MouseButton::Two;
			case GLFW_MOUSE_BUTTON_3: return ata::MouseButton::Three;
			case GLFW_MOUSE_BUTTON_4: return ata::MouseButton::Four;
			case GLFW_MOUSE_BUTTON_5: return ata::MouseButton::Five;
			case GLFW_MOUSE_BUTTON_6: return ata::MouseButton::Six;
			case GLFW_MOUSE_BUTTON_7: return ata::MouseButton::Seven;
			case GLFW_MOUSE_BUTTON_8: return ata::MouseButton::Eight;
			default: break;
		}
		return ata::MouseButton::None;
	}
	
	inline ata::KeyState translateKeyState(int state)
	{
		switch(state)
		{
			case GLFW_PRESS: return ata::KeyState::Press;
			case GLFW_REPEAT: return ata::KeyState::Repeat;
			default: break;
        	}
        	return ata::KeyState::Release;
	}

	inline ata::MouseButtonState translateMouseButtonState(int state)
	{
		return (state == GLFW_PRESS) ? ata::MouseButtonState::Press : ata::MouseButtonState::Release;
	}
    	//inline void joystickCallback(int jid, int eventType);
}

namespace ata
{
    	static Surface* getWrapperFromHandle(void* handle)
    	{
        	return static_cast<Surface*>(glfwGetWindowUserPointer(static_cast<GLFWwindow*>(handle)));
    	}

    	static void setWrapperFromHandle(void* handle, Surface* ptr)
    	{
        	glfwSetWindowUserPointer(static_cast<GLFWwindow*>(handle), ptr);
   	}

    	void keyCallback(GLFWwindow* window, int key, int scanCode, int state, int mods)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->keyEvent.emit(wrapper, translateKeyCode(key), scanCode, translateKeyState(state), translateModifierKeyBit(mods));
    	}

    	void charCallback(GLFWwindow* window, unsigned int codepoint)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->charEvent.emit(wrapper, codepoint);
    	}

    	void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->mouseButtonEvent.emit(wrapper, translateMouseButton(button), static_cast<MouseButtonState>(state), translateModifierKeyBit(mods));
    	}

    	void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->cursorPosEvent.emit(wrapper, xPos, yPos);
        	wrapper->m_cursor_pos.x = (int) xPos;
        	wrapper->m_cursor_pos.y = (int) yPos;
    	}

    	void cursorEnterCallback(GLFWwindow* window, int value)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->cursorEnterEvent.emit(wrapper, static_cast<bool>(value));
        	wrapper->m_cursor_enter = static_cast<bool>(value);
    	}

    	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->scrollEvent.emit(wrapper, xOffset, yOffset);
    	}

    	void dropCallback(GLFWwindow* window, int count, const char** pPaths)
    	{
        	std::vector<const char*> paths;
        	paths.reserve(count);

        	for(int i = 0; i < count; ++i)
        	{
            		paths.emplace_back(pPaths[i]);
        	}

        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->dropEvent.emit(wrapper, paths);
    	}

    	void posCallback(GLFWwindow* window, int xPos, int yPos)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->posEvent.emit(wrapper, xPos, yPos);
        	wrapper->m_window_pos.x = xPos;
        	wrapper->m_window_pos.y = yPos;
    	}

    	void sizeCallback(GLFWwindow* window, int width, int height)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->sizeEvent.emit(wrapper, width, height);
        	wrapper->m_window_size.x = width;
        	wrapper->m_window_size.y = height;
    	}

    	void closeCallback(GLFWwindow* window)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->closeEvent.emit(wrapper);
        	wrapper->m_quit = true;
    	}

    	void refreshCallback(GLFWwindow* window)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->refreshEvent.emit(wrapper);
    	}

    	void focusCallback(GLFWwindow* window, int value)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->focusEvent.emit(wrapper, value);
        	wrapper->m_focused = (bool) value;
    	}

    	void iconifyCallback(GLFWwindow* window, int value)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->iconifyEvent.emit(wrapper, value);
        	wrapper->m_iconified = (bool) value;
    	}

    	void maximizeCallback(GLFWwindow* window, int value)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->maximizeEvent.emit(wrapper, value);
        	wrapper->m_maximized = (bool) value;
    	}

    	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->framebufferSizeEvent.emit(wrapper, width, height);
        	wrapper->m_framebuffer_size.x = width;
        	wrapper->m_framebuffer_size.y = height;
    	}

    	void contentScaleCallback(GLFWwindow* window, float xScale, float yScale)
    	{
        	Surface* wrapper = getWrapperFromHandle(window);
        	wrapper->contentScaleEvent.emit(wrapper, xScale, yScale);
        	wrapper->m_content_scale.x = xScale;
        	wrapper->m_content_scale.y = yScale;
    	}

    	Surface::Surface() :
        	m_monitor           {nullptr},
        	m_user_pointer      {nullptr},
        	m_quit              {false},
        	m_focused           {true},
        	m_focus_on_show     {true},
        	m_iconified         {false},
        	m_auto_iconify      {false},
        	m_maximized         {false},
        	m_visible           {true},
        	m_resizable         {true},
        	m_topmost           {false},
        	m_decorated         {true},
        	m_cursor_enter      {false},
        	m_fullscreen        {false},
        	m_opacity           {1.f},
        	m_title             {""},
        	m_cursor_mode       {CursorMode::Normal},
        	m_window_dim_save   {0, 0, 0, 0},
        	m_window_size_limits{-1, -1, -1, -1},
        	m_aspect_ratio      {-1, -1},
        	m_content_scale     {1.f, 1.f},
        	m_cursor_pos        {0, 0},
        	m_window_size       {0, 0},
        	m_framebuffer_size  {0, 0},
        	m_window_pos        {0, 0},
        	m_context           {nullptr}
    	{
    	}

    	Surface::~Surface()
    	{
        	delete m_context;
    	}

    	void Surface::setUserPointer(void* user)
    	{
        	m_user_pointer = user;
    	}

    	void* Surface::getUserPointer()
    	{
        	return m_user_pointer;
    	}

    	bool Surface::create(WindowConfig conf)
	{
       		if(!conf.title)
        	{
            		conf.title = "Base Window";
		}

        	m_title = conf.title;
        	if(conf.monitor)
        	{
            		m_monitor = conf.monitor->m_handle;
		}

        	m_resizable = conf.resizable;
        	m_decorated = conf.decorated;
        	m_topmost = conf.floating;
        	m_focused = conf.focused;
        	m_focus_on_show = conf.focusOnShow;
        	m_auto_iconify = conf.autoIconify;

        	m_context = new GraphicsContext();
        	assert(m_context && "Failed to create context");

        	if(!conf.maximized)
        	{
            		ata::recti workArea;
            		glfwGetMonitorWorkarea(
                        	glfwGetPrimaryMonitor(),
                        	&workArea.x,
                        	&workArea.y,
                        	&workArea.w,
                        	&workArea.h);

            		if(conf.width == 0 || conf.height == 0)
            		{
                		m_window_size.x = workArea.w / 4;
                		m_window_size.y = workArea.h / 3;
                		conf.width = m_window_size.x;
                		conf.height = m_window_size.y;
            		}

            		m_window_pos.x = workArea.w / 2 - m_window_size.x / 2;
            		m_window_pos.y = workArea.h / 2 - m_window_size.y / 2;
        	}

        	// create the graphics context
        	if(!m_context->create(conf))
        	{
            		err() << "Failed to create surface" << std::endl;
            		makeContextCurrent(false);
            		return false;
        	}

        	makeContextCurrent(true);
        	if(!conf.maximized)
        	{
            		glfwSetWindowPos(static_cast<GLFWwindow*>(m_context->m_handle), m_window_pos.x, m_window_pos.y);
		}

        	setWrapperFromHandle(m_context->m_handle, this);
        	glfwSetWindowPosCallback(static_cast<GLFWwindow*>(m_context->m_handle), posCallback);
        	glfwSetWindowSizeCallback(static_cast<GLFWwindow*>(m_context->m_handle), sizeCallback);
        	glfwSetWindowCloseCallback(static_cast<GLFWwindow*>(m_context->m_handle), closeCallback);
        	glfwSetWindowRefreshCallback(static_cast<GLFWwindow*>(m_context->m_handle), refreshCallback);
        	glfwSetWindowFocusCallback(static_cast<GLFWwindow*>(m_context->m_handle), focusCallback);
        	glfwSetWindowIconifyCallback(static_cast<GLFWwindow*>(m_context->m_handle), iconifyCallback);
        	glfwSetWindowMaximizeCallback(static_cast<GLFWwindow*>(m_context->m_handle), maximizeCallback);
        	glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(m_context->m_handle), framebufferSizeCallback);
        	glfwSetWindowContentScaleCallback(static_cast<GLFWwindow*>(m_context->m_handle), contentScaleCallback);
        	glfwSetKeyCallback(static_cast<GLFWwindow*>(m_context->m_handle), keyCallback);
        	glfwSetCharCallback(static_cast<GLFWwindow*>(m_context->m_handle), charCallback);
        	glfwSetMouseButtonCallback(static_cast<GLFWwindow*>(m_context->m_handle), mouseButtonCallback);
        	glfwSetCursorPosCallback(static_cast<GLFWwindow*>(m_context->m_handle), cursorPosCallback);
        	glfwSetCursorEnterCallback(static_cast<GLFWwindow*>(m_context->m_handle), cursorEnterCallback);
        	glfwSetScrollCallback(static_cast<GLFWwindow*>(m_context->m_handle), scrollCallback);
        	glfwSetDropCallback(static_cast<GLFWwindow*>(m_context->m_handle), dropCallback);

        	return true;
    	}

    	bool Surface::isRunning() const
    	{
        	return !m_quit;
    	}

    	void Surface::swapBuffers()
    	{
        	glfwSwapBuffers(static_cast<GLFWwindow*>(m_context->m_handle));
    	}

    	void Surface::setAspectRatio(int x, int y)
    	{
        	glfwSetWindowAspectRatio(static_cast<GLFWwindow*>(m_context->m_handle), x, y);
        	m_aspect_ratio.x = x;
        	m_aspect_ratio.y = y;
    	}

    	void Surface::setAspectRatio(const ata::vec2i& aspectRatio)
    	{
        	setAspectRatio(aspectRatio.x, aspectRatio.y);
    	}

    	void Surface::setAutoIconify(bool autoIconify)
    	{
        	if(m_auto_iconify != autoIconify)
        	{
            		glfwSetWindowAttrib(static_cast<GLFWwindow*>(m_context->m_handle), GLFW_AUTO_ICONIFY, autoIconify);
            		m_auto_iconify = autoIconify;
        	}
    	}

    	void Surface::setClipboardString(const char* str)
    	{
        	glfwSetClipboardString(static_cast<GLFWwindow*>(m_context->m_handle), str);
    	}

    	void Surface::setCursorImage(const unsigned char* data, unsigned width, unsigned height, int x, int y)
    	{
        	GLFWimage image;
        	image.width = width;
        	image.height = height;
        	image.pixels = const_cast<unsigned char*>(data);

        	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
        	glfwSetCursor(static_cast<GLFWwindow*>(m_context->m_handle), cursor);
    	}

    	void Surface::setCursorPosition(int x, int y)
    	{
        	glfwSetCursorPos(static_cast<GLFWwindow*>(m_context->m_handle), x, y);
    	}

    	void Surface::setCursorPosition(const ata::vec2i& pos)
    	{
        	setCursorPosition(pos.x, pos.y);
    	}

    	void Surface::setCursorMode(CursorMode cursorMode)
    	{
        	if(m_cursor_mode != cursorMode)
        	{
            		glfwSetInputMode(static_cast<GLFWwindow*>(m_context->m_handle), GLFW_CURSOR, translateCursorMode(cursorMode));
            		m_cursor_mode = cursorMode;
        	}
    	}

    	void Surface::setDecorated(bool decorated)
    	{
        	if(decorated != m_decorated)
        	{
            		glfwSetWindowAttrib(static_cast<GLFWwindow*>(m_context->m_handle), GLFW_DECORATED, decorated);
            		m_decorated = decorated;
        	}
    	}

    	void Surface::setFocusOnShow(bool focus)
    	{
        	if(m_focus_on_show != focus)
        	{
            		glfwSetWindowAttrib(static_cast<GLFWwindow*>(m_context->m_handle), GLFW_FOCUS_ON_SHOW, focus);
            		m_focus_on_show = focus;
        	}
	}

    	void Surface::setIcon(const unsigned char* data, unsigned width, unsigned height)
    	{
        	GLFWimage image;
        	image.width = width;
        	image.height = height;
        	image.pixels = const_cast<unsigned char*>(data);

        	glfwSetWindowIcon(static_cast<GLFWwindow*>(m_context->m_handle), 1, &image);
    	}

    	void Surface::setOpacity(float opacity)
    	{
        	glfwSetWindowOpacity(static_cast<GLFWwindow*>(m_context->m_handle), opacity);
        	m_opacity = opacity;
    	}

    	void Surface::setPosition(int x, int y)
    	{
        	glfwSetWindowPos(static_cast<GLFWwindow*>(m_context->m_handle), x, y);
        	m_window_pos.x = x;
        	m_window_pos.y = y;
    	}

    	void Surface::setPosition(const ata::vec2i& pos)
    	{
        	setPosition(pos.x, pos.y);
    	}

    	void Surface::setResizable(bool resizable)
    	{
        	if(m_resizable != resizable)
        	{
            		glfwSetWindowAttrib(static_cast<GLFWwindow*>(m_context->m_handle), GLFW_RESIZABLE, resizable);
            		m_resizable = resizable;
        	}
    	}
	
    	void Surface::setTitle(const char* title)
    	{
        	assert(m_context->m_handle != nullptr && "context handle = NULL");
        	glfwSetWindowTitle(static_cast<GLFWwindow*>(m_context->m_handle), title);
        	m_title = title;
    	}

    	void Surface::setTopmost(bool topmost)
    	{
        	if(m_topmost != topmost)
        	{
            		glfwSetWindowAttrib(static_cast<GLFWwindow*>(m_context->m_handle), GLFW_FLOATING, topmost);
            		m_topmost = topmost;
        	}
    	}
	
    	void Surface::setSize(unsigned width, unsigned height)
    	{
        	glfwSetWindowSize(static_cast<GLFWwindow*>(m_context->m_handle), width, height);
        	m_window_size.x = width;
        	m_window_size.y = height;
    	}

    	void Surface::setSize(const ata::vec2u& dim)
    	{
        	setSize(dim.x, dim.y);
    	}

    	void Surface::setSizeLimits(int minW, int minH, int maxW, int maxH)
    	{
        	glfwSetWindowSizeLimits(static_cast<GLFWwindow*>(m_context->m_handle),
           	minW, minH, maxW, maxH);
		m_window_size_limits.x = minW;
		m_window_size_limits.y = minH;
        	m_window_size_limits.w = maxW;
        	m_window_size_limits.h = maxH;
    	}
	
    	void Surface::setSizeLimits(const ata::recti& dim)
    	{
        	setSizeLimits(dim.x, dim.y, dim.w, dim.h);
    	}

    	void Surface::setVisible(bool visible)
    	{
        	if(m_visible != visible)
        	{
            		visible ?
                	glfwShowWindow(static_cast<GLFWwindow*>(m_context->m_handle)) :
                	glfwHideWindow(static_cast<GLFWwindow*>(m_context->m_handle));
            		m_visible = visible;
        	}
    	}

    	void Surface::setFullscreen(bool toggle)
    	{
        	if(m_fullscreen != toggle)
        	{
            		if(toggle)
            		{
                		m_window_dim_save.x = m_window_pos.x;
                		m_window_dim_save.y = m_window_pos.y;
                		m_window_dim_save.w = m_window_size.x;
                		m_window_dim_save.h = m_window_size.y;

                		GLFWmonitor* monitor = m_monitor ?
                		static_cast<GLFWmonitor*>(m_monitor) :
                		glfwGetPrimaryMonitor();
                		const GLFWvidmode* currentMode = glfwGetVideoMode(monitor);
                		glfwSetWindowMonitor(static_cast<GLFWwindow*>(m_context->m_handle),
                    		monitor,
                    		0, 0,
                    		currentMode->width,
                    		currentMode->height,
                    		currentMode->refreshRate);
            		}
            		else
            		{
                		glfwSetWindowMonitor(static_cast<GLFWwindow*>(m_context->m_handle),
                    			NULL,
                    			m_window_dim_save.x,
                    			m_window_dim_save.y,
					m_window_dim_save.w,
                    			m_window_dim_save.h,
                    			GLFW_DONT_CARE);
            		}
            		m_fullscreen = toggle;
        	}
    	}

    	bool Surface::isAutoIconified() const
    	{
        	return m_auto_iconify;
    	}
	
    	ata::vec2i Surface::getAspectRatio() const
    	{
        	return m_aspect_ratio;
    	}

    	const char* Surface::getClipboardString() const
    	{
        	return glfwGetClipboardString(static_cast<GLFWwindow*>(m_context->m_handle));
    	}

    	ata::vec2f Surface::getContentScale() const
    	{
        	return m_content_scale;
    	}

    	ata::vec2i Surface::getCursorPosition() const
    	{
        	return m_cursor_pos;
    	}

    	CursorMode Surface::getCursorMode() const
    	{
        	return m_cursor_mode;
    	}

    	ata::vec2u Surface::getFramebufferSize() const
    	{
        	return m_framebuffer_size;
    	}

    	bool Surface::isDecorated() const
    	{
        	return m_decorated;
    	}

    	bool Surface::isFocusedOnShow() const
    	{
        	return m_focus_on_show;
    	}

    	float Surface::getOpacity() const
    	{
        	return m_opacity;
    	}

    	ata::vec2i Surface::getPosition() const
    	{
        	return m_window_pos;
    	}

    	bool Surface::isResizable() const
    	{
        	return m_resizable;
    	}

    	const char* Surface::getTitle() const
    	{
        	return m_title;
    	}

    	bool Surface::isTopmost() const
    	{
        	return m_topmost;
    	}

    	ata::vec2u Surface::getSize() const
    	{
        	return m_window_size;
    	}

    	ata::recti Surface::getSizeLimits() const
    	{
        	return m_window_size_limits;
    	}

    	bool Surface::isVisible() const
    	{
        	return m_visible;
    	}

    	bool Surface::isFullscreen() const
    	{
        	return m_fullscreen;
    	}

    	bool Surface::hasFocus() const
    	{
        	return m_focused;
    	}

    	bool Surface::isMouseInside() const
    	{
        	return m_cursor_enter;
    	}

    	bool Surface::isIconified() const
    	{
        	return m_iconified;
    	}

    	bool Surface::isMaximized() const
    	{
        	return m_maximized;
    	}

    	void Surface::close()
    	{
        	glfwSetWindowShouldClose(static_cast<GLFWwindow*>(m_context->m_handle), true);
        	m_quit = true;
    	}

    	void Surface::iconify()
    	{
        	glfwIconifyWindow(static_cast<GLFWwindow*>(m_context->m_handle));
    	}

    	void Surface::maximize()
    	{
        	glfwMaximizeWindow(static_cast<GLFWwindow*>(m_context->m_handle));
    	}

    	void Surface::restore()
    	{
        	glfwRestoreWindow(static_cast<GLFWwindow*>(m_context->m_handle));
    	}

    	void Surface::focus()
    	{
        	glfwFocusWindow(static_cast<GLFWwindow*>(m_context->m_handle));
    	}

    	bool Surface::makeContextCurrent(bool set)
    	{
        	return m_context->makeCurrent(set);
    	}

	bool Surface::isContextCurrent() const
    	{
        	return m_context->isCurrent();
    	}
	
	bool Surface::rawMouseMotionSupported()
	{
		return glfwRawMouseMotionSupported();
	}
	
	double Surface::getTime()
	{
		return glfwGetTime();
	}
	
    	void Surface::setTime(double time)
	{
		glfwSetTime(time);
	}
	
    	SPuint64 Surface::getTimerValue()
	{
		return glfwGetTimerValue();
	}
	
    	SPuint64 Surface::getTimerFrequency()
	{
		return glfwGetTimerFrequency();
	}
}
