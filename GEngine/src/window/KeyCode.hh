#pragma once

#include <GLFW/glfw3.h>
namespace GE
{

enum class KeyCode
{
    Unknown = GLFW_KEY_UNKNOWN,
    Space = GLFW_KEY_SPACE,
    Apostrophe = GLFW_KEY_APOSTROPHE, /* ' */
    Comma = GLFW_KEY_COMMA,           /* , */
    Minus = GLFW_KEY_MINUS,           /* - */
    Period = GLFW_KEY_PERIOD,         /* . */
    Slash = GLFW_KEY_SLASH,           /* / */
    Zero = GLFW_KEY_0,
    One = GLFW_KEY_1,
    Two = GLFW_KEY_2,
    Three = GLFW_KEY_3,
    Four = GLFW_KEY_4,
    Five = GLFW_KEY_5,
    Six = GLFW_KEY_6,
    Seven = GLFW_KEY_7,
    Eight = GLFW_KEY_8,
    Nine = GLFW_KEY_9,
    SemiColon = GLFW_KEY_SEMICOLON, /* ; */
    Equal = GLFW_KEY_EQUAL,         /* = */
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    LeftBracket = GLFW_KEY_LEFT_BRACKET,   /* [ */
    BackLash = GLFW_KEY_BACKSLASH,         /* \ */
    RightBracket = GLFW_KEY_RIGHT_BRACKET, /* ] */
    GraveAccent = GLFW_KEY_GRAVE_ACCENT,   /* ` */
    // Unknown = GLFW_KEY_WORLD_1,       /* non-US #1 */
    // Unknown = GLFW_KEY_WORLD_2,       /* non-US #2 */
    Escape = GLFW_KEY_ESCAPE,
    Enter = GLFW_KEY_ENTER,
    Tab = GLFW_KEY_TAB,
    BackSpace = GLFW_KEY_BACKSPACE,
    Insert = GLFW_KEY_INSERT,
    Delete = GLFW_KEY_DELETE,
    RightArrow = GLFW_KEY_RIGHT,
    LeftArrow = GLFW_KEY_LEFT,
    DownArrow = GLFW_KEY_DOWN,
    UpArrow = GLFW_KEY_UP,
    PageUp = GLFW_KEY_PAGE_UP,
    PageDown = GLFW_KEY_PAGE_DOWN,
    Home = GLFW_KEY_HOME,
    End = GLFW_KEY_END,
    CapsLock = GLFW_KEY_CAPS_LOCK,
    ScrollLock = GLFW_KEY_SCROLL_LOCK,
    NumLock = GLFW_KEY_NUM_LOCK,
    PrintScreen = GLFW_KEY_PRINT_SCREEN,
    Pause = GLFW_KEY_PAUSE,
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    // Unknown = GLFW_KEY_F13,
    // Unknown = GLFW_KEY_F14,
    // Unknown = GLFW_KEY_F15,
    // Unknown = GLFW_KEY_F16,
    // Unknown = GLFW_KEY_F17,
    // Unknown = GLFW_KEY_F18,
    // Unknown = GLFW_KEY_F19,
    // Unknown = GLFW_KEY_F20,
    // Unknown = GLFW_KEY_F21,
    // Unknown = GLFW_KEY_F22,
    // Unknown = GLFW_KEY_F23,
    // Unknown = GLFW_KEY_F24,
    // Unknown = GLFW_KEY_F25,
    Num0 = GLFW_KEY_KP_0,
    Num1 = GLFW_KEY_KP_1,
    Num2 = GLFW_KEY_KP_2,
    Num3 = GLFW_KEY_KP_3,
    Num4 = GLFW_KEY_KP_4,
    Num5 = GLFW_KEY_KP_5,
    Num6 = GLFW_KEY_KP_6,
    Num7 = GLFW_KEY_KP_7,
    Num8 = GLFW_KEY_KP_8,
    Num9 = GLFW_KEY_KP_9,
    // Unknown = GLFW_KEY_KP_DECIMAL,
    Divide = GLFW_KEY_KP_DIVIDE,
    Multiply = GLFW_KEY_KP_MULTIPLY,
    Subtract = GLFW_KEY_KP_SUBTRACT,
    Add = GLFW_KEY_KP_ADD,
    // Unknown = GLFW_KEY_KP_ENTER,
    // Unknown = GLFW_KEY_KP_EQUAL,
    LeftShift = GLFW_KEY_LEFT_SHIFT,
    leftControl = GLFW_KEY_LEFT_CONTROL,
    LeftAlt = GLFW_KEY_LEFT_ALT,
    LeftSuper = GLFW_KEY_LEFT_SUPER,
    RightShift = GLFW_KEY_RIGHT_SHIFT,
    RightControl = GLFW_KEY_RIGHT_CONTROL,
    RightAlt = GLFW_KEY_RIGHT_ALT,
    RightSuper = GLFW_KEY_RIGHT_SUPER,
    // Unknown = GLFW_KEY_MENU,
    // Unknown = GLFW_KEY_LAST

};

enum class MouseKey : int
{
    LeftButton = GLFW_MOUSE_BUTTON_LEFT,
    RightButton = GLFW_MOUSE_BUTTON_RIGHT,
    MiddleButton = GLFW_MOUSE_BUTTON_MIDDLE
};

inline constexpr int toGLFW(KeyCode code) { return static_cast<int>(code); }
inline constexpr KeyCode toKeyCode(int code) { return static_cast<KeyCode>(code); }

inline constexpr int toGLFW(MouseKey code) { return static_cast<int>(code); }
inline constexpr MouseKey toMouseKey(int code) { return static_cast<MouseKey>(code); }

}