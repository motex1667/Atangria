#ifndef ATA_APIDEFS_H
#define ATA_APIDEFS_H
#include "ATA/config.h"

namespace ata
{
    enum class ClientApi : SPint
    {
        None,
        OpenGl,
        OpenGles
    };

    enum class ContextCreationApi : SPint
    {
        Native,
        Egl,
        OsMesa
    };

    enum class ContextRobustness : SPint
    {
        NoRobustness,
        NoResetNotification,
        LoseContextOnReset
    };

    enum class ContextReleaseBehavior : SPint
    {
        None,
        Any,
        Flush
    };

    enum class OpenGlProfile : SPint
    {
        Any,
        Compat,
        Core
    };
	
    enum class CursorMode : SPint
    {
        Normal,
        Disabled,
        Hidden
    };

    enum class KeyCode : SPint
    {
        None = 0,
        Space,
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,
        Zero,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Semicolon,
        Equal,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,
        World1,
        World2,
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,
        KeyPad0,
        KeyPad1,
        KeyPad2,
        KeyPad3,
        KeyPad4,
        KeyPad5,
        KeyPad6,
        KeyPad7,
        KeyPad8,
        KeyPad9,
        KeyPadDecimal,
        KeyPadDivide,
        KeyPadMultiply,
        KeyPadSubtract,
        KeyPadAdd,
        KeyPadEnter,
        KeyPadEqual,
        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,
        MaxValue = Menu
    };

    enum class ModifierKeyBit : SPint
    {
		None = 0,
        Shift,
        Control,
        Alt,
        Super,
        CapsLock,
        NumLock
    };

    enum class MouseButton : SPint
    {
		None = 0,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Left,
        Right,
        Middle,
        MaxValue
    };

    enum class KeyState : SPint
    {
        Press = 0,
        Release,
        Repeat
    };

    enum class MouseButtonState : SPint
    {
        Press = 0,
        Release
    };
	
	struct WindowConfig
    {
        unsigned int width = 0;
        unsigned int height = 0;
        const char* title = nullptr;
        class Monitor* monitor = nullptr;
        bool resizable = true;
        bool visible = true;
        bool decorated = true;
        bool focused = true;
        bool autoIconify = false;
        bool floating = false;
        bool maximized = false;
        bool transparentFramebuffer = false;
        bool focusOnShow = true;
        bool scaleToMonitor = false;
        int redBits = 8;
        int greenBits = 8;
        int blueBits = 8;
        int alphaBits = 8;
        int depthBits = 24;
        int stencilBits = 8;
        int accumRedBits = 0;
        int accumGreenBits = 0;
        int accumBlueBits = 0;
        int accumAlphaBits = 0;
        int auxBuffers = 0;
        int samples = 0;
        int refreshRate = -1;
        bool stereo = false;
        bool srgbCapable = false;
        bool doubleBuffer = true;

        // MacOSX specific properties
        bool cocoaRetinaFramebuffer = false;
        const char* cocoaFrameName = "";
        bool cocoaGraphicsSwitching = false;

        // X11 specific properties
        const char* x11ClassName = "";
        const char* x11InstanceName = "";
    };
}

#endif
