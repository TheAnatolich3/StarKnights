#ifndef GENERAL_UTILS_HPP
#define GENERAL_UTILS_HPP
#include <glm/glm.hpp>
#include <string>
#include <string_view>
#include <fstream>

#define XSTRINGIFY(A) STRINGIFY(A)
#define STRINGIFY(A) #A

namespace utils
{
	inline size_t genUniqueObjectId()
	{
		static size_t id = 0;
		return ++id;
	}

    struct color
    {
        explicit color(std::uint32_t rgba) : _rgba(rgba) {}
        color(glm::vec4 color)
        {
            this->setColor(color);
        }

        glm::vec4 getColor() const
        {
            std::uint32_t r = (_rgba & 0x000000FF);
            std::uint32_t g = (_rgba & 0x0000FF00) >> 8;
            std::uint32_t b = (_rgba & 0x00FF0000) >> 16;
            std::uint32_t a = (_rgba & 0xFF000000) >> 24;

            return glm::vec4(r, g, b, a) / 255.0f;
        }

        void setColor(glm::vec4 color)
        {
            assert(color.r <= 1 && color.r >= 0);
            assert(color.g <= 1 && color.g >= 0);
            assert(color.b <= 1 && color.b >= 0);
            assert(color.a <= 1 && color.a >= 0);

            auto r = static_cast<std::uint32_t>(color.r * 255);
            auto g = static_cast<std::uint32_t>(color.g * 255);
            auto b = static_cast<std::uint32_t>(color.b * 255);
            auto a = static_cast<std::uint32_t>(color.a * 255);

            _rgba = a << 24 | b << 16 | g << 8 | r;
        }

        uint32_t getRgba() const
        {
            return _rgba;
        }

        void setRgba(uint32_t rgba)
        {
            _rgba = rgba;
        }

        std::uint32_t _rgba = 0;
    };

	enum class KeyCode
	{
		UNKNOWN = 0,
		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,
		NUM_1 = 30,
		NUM_2 = 31,
		NUM_3 = 32,
		NUM_4 = 33,
		NUM_5 = 34,
		NUM_6 = 35,
		NUM_7 = 36,
		NUM_8 = 37,
		NUM_9 = 38,
		NUM_0 = 39,
		RETURN = 40,
		ESCAPE = 41,
		BACKSPACE = 42,
		TAB = 43,
		SPACE = 44,
		MINUS = 45,
		EQUALS = 46,
		LEFTBRACKET = 47,
		RIGHTBRACKET = 48,
		BACKSLASH = 49,
		NONUSHASH = 50,
		SEMICOLON = 51,
		APOSTROPHE = 52,
		GRAVE = 53, COMMA = 54,
		PERIOD = 55,
		SLASH = 56,
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
		DELETE = 76,
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
		NONUSBACKSLASH = 100,
		APPLICATION = 101,
		POWER = 102,
		KP_EQUALS = 103,
		F13 = 104,
		F14 = 105,
		F15 = 106,
		F16 = 107,
		F17 = 108,
		F18 = 109,
		F19 = 110,
		F20 = 111,
		F21 = 112,
		F22 = 113,
		F23 = 114,
		F24 = 115,
		EXECUTE = 116,
		HELP = 117,
		MENU = 118,
		SELECT = 119,
		STOP = 120,
		AGAIN = 121,
		UNDO = 122,
		CUT = 123,
		COPY = 124,
		PASTE = 125,
		FIND = 126,
		MUTE = 127,
		VOLUMEUP = 128,
		VOLUMEDOWN = 129,
		KP_COMMA = 133,
		KP_EQUALSAS400 = 134,
		INTERNATIONAL1 = 135,
		INTERNATIONAL2 = 136,
		INTERNATIONAL3 = 137,
		INTERNATIONAL4 = 138,
		INTERNATIONAL5 = 139,
		INTERNATIONAL6 = 140,
		INTERNATIONAL7 = 141,
		INTERNATIONAL8 = 142,
		INTERNATIONAL9 = 143,
		LANG1 = 144,
		LANG2 = 145,
		LANG3 = 146,
		LANG4 = 147,
		LANG5 = 148,
		LANG6 = 149,
		LANG7 = 150,
		LANG8 = 151,
		LANG9 = 152,
		ALTERASE = 153,
		SYSREQ = 154,
		CANCEL = 155,
		CLEAR = 156,
		PRIOR = 157,
		RETURN2 = 158,
		SEPARATOR = 159,
		OUT = 160,
		OPER = 161,
		CLEARAGAIN = 162,
		CRSEL = 163,
		EXSEL = 164,
		KP_00 = 176,
		KP_000 = 177,
		THOUSANDSSEPARATOR = 178,
		DECIMALSEPARATOR = 179,
		CURRENCYUNIT = 180,
		CURRENCYSUBUNIT = 181,
		KP_LEFTPAREN = 182,
		KP_RIGHTPAREN = 183,
		KP_LEFTBRACE = 184,
		KP_RIGHTBRACE = 185,
		KP_TAB = 186,
		KP_BACKSPACE = 187,
		KP_A = 188,
		KP_B = 189,
		KP_C = 190,
		KP_D = 191,
		KP_E = 192,
		KP_F = 193,
		KP_XOR = 194,
		KP_POWER = 195,
		KP_PERCENT = 196,
		KP_LESS = 197,
		KP_GREATER = 198,
		KP_AMPERSAND = 199,
		KP_DBLAMPERSAND = 200,
		KP_VERTICALBAR = 201,
		KP_DBLVERTICALBAR = 202,
		KP_COLON = 203,
		KP_HASH = 204,
		KP_SPACE = 205,
		KP_AT = 206,
		KP_EXCLAM = 207,
		KP_MEMSTORE = 208,
		KP_MEMRECALL = 209,
		KP_MEMCLEAR = 210,
		KP_MEMADD = 211,
		KP_MEMSUBTRACT = 212,
		KP_MEMMULTIPLY = 213,
		KP_MEMDIVIDE = 214,
		KP_PLUSMINUS = 215,
		KP_CLEAR = 216,
		KP_CLEARENTRY = 217,
		KP_BINARY = 218,
		KP_OCTAL = 219,
		KP_DECIMAL = 220,
		KP_HEXADECIMAL = 221,
		LCTRL = 224,
		LSHIFT = 225,
		LALT = 226,
		LGUI = 227,
		RCTRL = 228,
		RSHIFT = 229,
		RALT = 230,
		RGUI = 231,
		MODE = 257,
		AUDIONEXT = 258,
		AUDIOPREV = 259,
		AUDIOSTOP = 260,
		AUDIOPLAY = 261,
		AUDIOMUTE = 262,
		MEDIASELECT = 263,
		WWW = 264,
		MAIL = 265,
		CALCULATOR = 266,
		COMPUTER = 267,
		AC_SEARCH = 268,
		AC_HOME = 269,
		AC_BACK = 270,
		AC_FORWARD = 271,
		AC_STOP = 272,
		AC_REFRESH = 273,
		AC_BOOKMARKS = 274,
		BRIGHTNESSDOWN = 275,
		BRIGHTNESSUP = 276,
		DISPLAYSWITCH = 277,
		KBDILLUMTOGGLE = 278,
		KBDILLUMDOWN = 279,
		KBDILLUMUP = 280,
		EJECT = 281,
		SLEEP = 282,
		APP1 = 283,
		APP2 = 284,
		NUM_SCANCODES = 512
	};
}

#endif GENERAL_UTILS_HPP
