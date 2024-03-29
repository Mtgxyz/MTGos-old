#ifndef _KEYMAP_DE_HPP
#define _KEYMAP_DE_HPP
#include <keycodes.hpp>
#define SHIFT 1
#define CTRL 2
#define ALT 4
char keymap[8][0x80] = {
	"\0\0001234567890\xe1\0\b\0qwertzuiop\x81+\n\0asdfghjkl\x94\x84^\0#yxcvbnm,.-\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\000789-456+1230,<\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // No modifier
	"\0\000!\"\0$%&/()=?`\b\0QWERTZUIOP\x9A*\n\0ASDFGHJKL\x99\x8e\xF8\0'YXCVBNM;:_\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,>\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Shift modifier
	"\0\0001234567890\xe1\0\b\0qwertzuiop\x81+\n\0asdfghjkl\x94\x84^\0#yxcvbnm,.-\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,<\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Control modifier
	"\0\000!\"\0$%&/()=?`\b\0QWERTZUIOP\x9A*\n\0ASDFGHJKL\x99\x8e\xF8\0'YXCVBNM;:_\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,>\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Control+Shift modifiers
	"\0\0001234567890\xe1\0\b\0qwertzuiop\x81+\n\0asdfghjkl\x94\x84^\0#yxcvbnm,.-\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,<\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Alt modifier
	"\0\000!\"\0$%&/()=?`\b\0QWERTZUIOP\x9A*\n\0ASDFGHJKL\x99\x8e\xF8\0'YXCVBNM;:_\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,>\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Alt+Shift modifiers
	"\0\0001\xFD\x33\xAC\xAB\xAA{[]}\\\xa7\b\0@w\xEErtzui\xEDp\x81~\n\0\x91sdfghjkl\x94^\0#\xAF\xAE\x9Bvbn\xe6,.-\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,|\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Control+Alt modifiers
	"\0\000\xAD\"\x9C\x0F%&/(\xF1\xF8\xA8`\b\0\xEAW\xEERT\x9DUIOP\xF8*\n\0\x92SD\xA6GHJ&L\x99\x8e\xF8\0|YXCVBN\xF8;\xF6_\0*\0 \0\0\0\0\0\0\0\0\0\0\0\0\0789-456+1230,|\0\0\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", // Control+Shift modifiers
};
#endif
