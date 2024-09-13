#pragma once

#include "WilloEngine/PimplClass.hpp"

#include <functional>

namespace WilloEngine
{
    enum class SCAN_CODE : uint32_t
    {
        CAPSLOCK = 57,

        F1 = 58,
        F2 = 59,
        F3 = 60,
        F4 = 61,
        F5 = 62,
        F6 = 63,
        F7 = 64,
        F8 = 65,
        F9 = 66,
        F10 = 67,
        F11 = 68,
        F12 = 69,

        PRINTSCREEN = 70,
        SCROLLLOCK = 71,
        PAUSE = 72,
        INSERT = 73,
        HOME = 74,
        PAGEUP = 75,
        DEL = 76,
        END = 77,
        PAGEDOWN = 78,
        RIGHT = 79,
        LEFT = 80,
        DOWN = 81,
        UP = 82,

        NUMLOCKCLEAR = 83, 
        KP_DIVIDE = 84,
        KP_MULTIPLY = 85,
        KP_MINUS = 86,
        KP_PLUS = 87,
        KP_ENTER = 88,
        KP_1 = 89,
        KP_2 = 90,
        KP_3 = 91,
        KP_4 = 92,
        KP_5 = 93,
        KP_6 = 94,
        KP_7 = 95,
        KP_8 = 96,
        KP_9 = 97,
        KP_0 = 98,
        KP_PERIOD = 99,
    };

    #define WILLO_ENGINE_SCANCODE_MASK (1<<30)
    #define WILLO_ENGINE_SCANCODE_TO_KEYCODE(x) ((uint32_t)x | WILLO_ENGINE_SCANCODE_MASK)

    // effectively matches up with the keycode enum from SDL2
    enum class KEY_CODE : uint32_t
    {
        KEY_UNKNOWN = 0,

        KEY_RETURN = '\r',
        KEY_ESCAPE = '\x1B',
        KEY_BACKSPACE = '\b',
        KEY_TAB = '\t',
        KEY_SPACE = ' ',
        KEY_EXCLAIM = '!',
        KEY_QUOTEDBL = '"',
        KEY_HASH = '#',
        KEY_PERCENT = '%',
        KEY_DOLLAR = '$',
        KEY_AMPERSAND = '&',
        KEY_QUOTE = '\'',
        KEY_LEFTPAREN = '(',
        KEY_RIGHTPAREN = ')',
        KEY_ASTERISK = '*',
        KEY_PLUS = '+',
        KEY_COMMA = ',',
        KEY_MINUS = '-',
        KEY_PERIOD = '.',
        KEY_SLASH = '/',
        KEY_0 = '0',
        KEY_1 = '1',
        KEY_2 = '2',
        KEY_3 = '3',
        KEY_4 = '4',
        KEY_5 = '5',
        KEY_6 = '6',
        KEY_7 = '7',
        KEY_8 = '8',
        KEY_9 = '9',
        KEY_COLON = ':',
        KEY_SEMICOLON = ';',
        KEY_LESS = '<',
        KEY_EQUALS = '=',
        KEY_GREATER = '>',
        KEY_QUESTION = '?',
        KEY_AT = '@',

        KEY_LEFTBRACKET = '[',
        KEY_BACKSLASH = '\\',
        KEY_RIGHTBRACKET = ']',
        KEY_CARET = '^',
        KEY_UNDERSCORE = '_',
        KEY_BACKQUOTE = '`',
        KEY_A = 'a',
        KEY_B = 'b',
        KEY_C = 'c',
        KEY_D = 'd',
        KEY_E = 'e',
        KEY_F = 'f',
        KEY_G = 'g',
        KEY_H = 'h',
        KEY_I = 'i',
        KEY_J = 'j',
        KEY_K = 'k',
        KEY_L = 'l',
        KEY_M = 'm',
        KEY_N = 'n',
        KEY_O = 'o',
        KEY_P = 'p',
        KEY_Q = 'q',
        KEY_R = 'r',
        KEY_S = 's',
        KEY_T = 't',
        KEY_U = 'u',
        KEY_V = 'v',
        KEY_W = 'w',
        KEY_X = 'x',
        KEY_Y = 'y',
        KEY_Z = 'z',
        
        SDLK_CAPSLOCK = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::CAPSLOCK),

        SDLK_F1 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F1),
        SDLK_F2 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F2),
        SDLK_F3 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F3),
        SDLK_F4 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F4),
        SDLK_F5 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F5),
        SDLK_F6 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F6),
        SDLK_F7 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F7),
        SDLK_F8 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F8),
        SDLK_F9 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F9),
        SDLK_F10 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F10),
        SDLK_F11 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F11),
        SDLK_F12 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::F12),

        SDLK_PRINTSCREEN = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::PRINTSCREEN),
        SDLK_SCROLLLOCK = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::SCROLLLOCK),
        SDLK_PAUSE = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::PAUSE),
        SDLK_INSERT = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::INSERT),
        SDLK_HOME = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::HOME),
        SDLK_PAGEUP = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::PAGEUP),
        SDLK_DELETE = '\x7F',
        SDLK_END = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::END),
        SDLK_PAGEDOWN = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::PAGEDOWN),
        SDLK_RIGHT = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::RIGHT),
        SDLK_LEFT = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::LEFT),
        SDLK_DOWN = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::DOWN),
        SDLK_UP = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::UP),

        SDLK_NUMLOCKCLEAR = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::NUMLOCKCLEAR),
        SDLK_KP_DIVIDE = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_DIVIDE),
        SDLK_KP_MULTIPLY = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_MULTIPLY),
        SDLK_KP_MINUS = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_MINUS),
        SDLK_KP_PLUS = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_PLUS),
        SDLK_KP_ENTER = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_ENTER),
        SDLK_KP_1 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_1),
        SDLK_KP_2 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_2),
        SDLK_KP_3 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_3),
        SDLK_KP_4 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_4),
        SDLK_KP_5 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_5),
        SDLK_KP_6 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_6),
        SDLK_KP_7 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_7),
        SDLK_KP_8 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_8),
        SDLK_KP_9 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_9),
        SDLK_KP_0 = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_0),
        SDLK_KP_PERIOD = WILLO_ENGINE_SCANCODE_TO_KEYCODE(SCAN_CODE::KP_PERIOD),
    };

    enum class INPUT_EVENT_TYPE
    {
        KEY_PRESSED,
        KEY_RELEASED
    };

    class InputManager : private PimplClass<struct ImplInputManager>
    {
    public:
        // if useGetKey is false, then GetKey() will not work, perf may better
        // (not yet benchmarked, unsure)
        static bool Create(InputManager& inputManager, bool useGetKey = true);

        void Update();

        void ReceiveKeypressEvent(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType);

        bool GetKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType);

        void SubscribeKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType, std::function<void()> callback);
        void SubscribeKey(INPUT_EVENT_TYPE eventType, std::function<void(KEY_CODE)> callback);
    };
}
