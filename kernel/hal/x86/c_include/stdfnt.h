//Thanks to masterq32 for this font!
//You should check out his OS project (https://github.com/MasterQ32/DasOS)
uint8_t font[256][8] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x0D, 0x12, 0x12, 0x09, 0x09, 0x00 }, // ?
	{ 0x00, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00 }, // ?
	{ 0x00, 0x00, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00 }, // ?
	{ 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00 }, // ?
	{ 0x00, 0x02, 0x06, 0x0E, 0x06, 0x02, 0x00, 0x00 }, // ?
	{ 0x04, 0x0E, 0x1F, 0x0E, 0x0E, 0x00, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x0E, 0x0E, 0x1F, 0x0E, 0x04, 0x00 }, // ?
	{ 0x08, 0x14, 0x04, 0x04, 0x04, 0x05, 0x02, 0x00 }, // ?
	{ 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x00, 0x0E, 0x0A, 0x0E, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x00, 0x04, 0x0E, 0x04, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x00, 0x07, 0x02, 0x02, 0x02, 0x00 }, // ?
	{ 0x06, 0x08, 0x06, 0x08, 0x06, 0x00, 0x00, 0x00 }, // ?
	{ 0x1F, 0x03, 0x03, 0x0F, 0x03, 0x03, 0x03, 0x00 }, // ?
	{ 0x1C, 0x04, 0x04, 0x04, 0x05, 0x06, 0x04, 0x00 }, // ?
	{ 0x18, 0x10, 0x13, 0x10, 0x10, 0x00, 0x00, 0x00 }, // ?
	{ 0x06, 0x08, 0x04, 0x02, 0x0E, 0x00, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x10, 0x08, 0x04, 0x02, 0x1F, 0x00 }, // ?
	{ 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00 }, // ?
	{ 0x0D, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 }, // ?
	{ 0x0E, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00 }, // ?
	{ 0x10, 0x0C, 0x03, 0x0C, 0x10, 0x00, 0x1F, 0x00 }, // ?
	{ 0x08, 0x08, 0x1F, 0x04, 0x1F, 0x02, 0x02, 0x00 }, // ?
	{ 0x01, 0x06, 0x18, 0x06, 0x01, 0x00, 0x1F, 0x00 }, // ?
	{ 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x1E, 0x02, 0x0E, 0x02, 0x1E, 0x00 }, // ?
	{ 0x00, 0x04, 0x08, 0x1F, 0x08, 0x04, 0x00, 0x00 }, // ?
	{ 0x00, 0x00, 0x1D, 0x15, 0x15, 0x15, 0x1D, 0x00 }, // ?
	{ 0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x04, 0x00 }, // ?
	{ 0x04, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04, 0x00 }, // ?
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, //
	{ 0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00 }, // !
	{ 0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00 }, // "
	{ 0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00 }, // #
	{ 0x02, 0x0A, 0x0E, 0x08, 0x08, 0x00, 0x00, 0x00 }, // $
	{ 0x03, 0x13, 0x08, 0x04, 0x02, 0x19, 0x18, 0x00 }, // %
	{ 0x02, 0x05, 0x05, 0x02, 0x15, 0x09, 0x16, 0x00 }, // &
	{ 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '
	{ 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00 }, // (
	{ 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02, 0x00 }, // )
	{ 0x00, 0x04, 0x15, 0x0E, 0x15, 0x04, 0x00, 0x00 }, // *
	{ 0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00 }, // +
	{ 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0x02, 0x00 }, // ,
	{ 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00 }, // -
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00 }, // .
	{ 0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00 }, // /
	{ 0x0E, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0E, 0x00 }, // 0
	{ 0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // 1
	{ 0x0E, 0x11, 0x10, 0x08, 0x04, 0x02, 0x1F, 0x00 }, // 2
	{ 0x1F, 0x08, 0x04, 0x08, 0x10, 0x11, 0x0E, 0x00 }, // 3
	{ 0x08, 0x0C, 0x0A, 0x09, 0x1F, 0x08, 0x08, 0x00 }, // 4
	{ 0x1F, 0x01, 0x0F, 0x10, 0x10, 0x11, 0x0E, 0x00 }, // 5
	{ 0x0C, 0x02, 0x01, 0x0F, 0x11, 0x11, 0x0E, 0x00 }, // 6
	{ 0x1F, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02, 0x00 }, // 7
	{ 0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00 }, // 8
	{ 0x0E, 0x11, 0x11, 0x1E, 0x10, 0x08, 0x06, 0x00 }, // 9
	{ 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x00 }, // :
	{ 0x00, 0x06, 0x06, 0x00, 0x06, 0x04, 0x02, 0x00 }, // ;
	{ 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00 }, // <
	{ 0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00 }, // =
	{ 0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00 }, // >
	{ 0x0E, 0x11, 0x10, 0x08, 0x04, 0x00, 0x04, 0x00 }, // ?
	{ 0x0E, 0x11, 0x15, 0x1D, 0x05, 0x01, 0x1E, 0x00 }, // @
	{ 0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00 }, // A
	{ 0x0F, 0x11, 0x11, 0x0F, 0x11, 0x11, 0x0F, 0x00 }, // B
	{ 0x0E, 0x11, 0x01, 0x01, 0x01, 0x11, 0x0E, 0x00 }, // C
	{ 0x0F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0F, 0x00 }, // D
	{ 0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x1F, 0x00 }, // E
	{ 0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01, 0x00 }, // F
	{ 0x0E, 0x11, 0x01, 0x1D, 0x11, 0x11, 0x1E, 0x00 }, // G
	{ 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00 }, // H
	{ 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // I
	{ 0x1C, 0x08, 0x08, 0x08, 0x08, 0x09, 0x06, 0x00 }, // J
	{ 0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11, 0x00 }, // K
	{ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1F, 0x00 }, // L
	{ 0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00 }, // M
	{ 0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x00 }, // N
	{ 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // O
	{ 0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00 }, // P
	{ 0x0E, 0x11, 0x11, 0x11, 0x15, 0x09, 0x16, 0x00 }, // Q
	{ 0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11, 0x00 }, // R
	{ 0x1E, 0x01, 0x01, 0x0E, 0x10, 0x10, 0x0F, 0x00 }, // S
	{ 0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00 }, // T
	{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // U
	{ 0x11, 0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00 }, // V
	{ 0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0A, 0x00 }, // W
	{ 0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00 }, // X
	{ 0x11, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x00 }, // Y
	{ 0x1F, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1F, 0x00 }, // Z
	{ 0x0C, 0x12, 0x11, 0x1F, 0x11, 0x09, 0x06, 0x00 }, // [
	{ 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00 }, // \d
	{ 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x06, 0x00 }, // ]
	{ 0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ^
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00 }, // _
	{ 0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 }, // `
	{ 0x00, 0x00, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00 }, // a
	{ 0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x0F, 0x00 }, // b
	{ 0x00, 0x00, 0x0E, 0x01, 0x01, 0x11, 0x0E, 0x00 }, // c
	{ 0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1E, 0x00 }, // d
	{ 0x00, 0x00, 0x0E, 0x11, 0x1F, 0x01, 0x0E, 0x00 }, // e
	{ 0x0C, 0x12, 0x02, 0x07, 0x02, 0x02, 0x02, 0x00 }, // f
	{ 0x00, 0x1E, 0x11, 0x11, 0x1E, 0x10, 0x0E, 0x00 }, // g
	{ 0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x11, 0x00 }, // h
	{ 0x04, 0x00, 0x06, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // i
	{ 0x08, 0x00, 0x0C, 0x08, 0x08, 0x09, 0x06, 0x00 }, // j
	{ 0x02, 0x02, 0x12, 0x0A, 0x06, 0x0A, 0x12, 0x00 }, // k
	{ 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // l
	{ 0x00, 0x00, 0x0B, 0x15, 0x15, 0x11, 0x11, 0x00 }, // m
	{ 0x00, 0x00, 0x0D, 0x13, 0x11, 0x11, 0x11, 0x00 }, // n
	{ 0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // o
	{ 0x00, 0x00, 0x0F, 0x11, 0x0F, 0x01, 0x01, 0x00 }, // p
	{ 0x00, 0x00, 0x16, 0x19, 0x1E, 0x10, 0x10, 0x00 }, // q
	{ 0x00, 0x00, 0x0D, 0x13, 0x01, 0x01, 0x01, 0x00 }, // r
	{ 0x00, 0x00, 0x0E, 0x01, 0x0E, 0x10, 0x0F, 0x00 }, // s
	{ 0x02, 0x02, 0x07, 0x02, 0x02, 0x12, 0x0C, 0x00 }, // t
	{ 0x00, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00 }, // u
	{ 0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00 }, // v
	{ 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00 }, // w
	{ 0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00 }, // x
	{ 0x00, 0x00, 0x11, 0x11, 0x1E, 0x10, 0x0E, 0x00 }, // y
	{ 0x00, 0x00, 0x1F, 0x08, 0x04, 0x02, 0x1F, 0x00 }, // z
	{ 0x18, 0x04, 0x04, 0x02, 0x04, 0x04, 0x18, 0x00 }, // {
	{ 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00 }, // |
	{ 0x03, 0x04, 0x04, 0x08, 0x04, 0x04, 0x03, 0x00 }, // }
	{ 0x00, 0x02, 0x15, 0x08, 0x00, 0x00, 0x00, 0x00 }, // ~
	{ 0x1F, 0x1F, 0x11, 0x1F, 0x11, 0x1F, 0x1F, 0x00 }, // ?
	{ 0x00, 0x00, 0x0E, 0x0A, 0x0A, 0x0A, 0x0E, 0x00 }, // ?
	{ 0x00, 0x00, 0x04, 0x06, 0x04, 0x04, 0x04, 0x00 }, // ?
	{ 0x00, 0x00, 0x06, 0x08, 0x04, 0x02, 0x0E, 0x00 }, // ?
	{ 0x00, 0x00, 0x06, 0x08, 0x04, 0x08, 0x06, 0x00 }, // ?
	{ 0x00, 0x00, 0x02, 0x0A, 0x0E, 0x08, 0x08, 0x00 }, // ?
	{ 0x00, 0x00, 0x0E, 0x02, 0x06, 0x08, 0x06, 0x00 }, // ?
	{ 0x00, 0x00, 0x0C, 0x02, 0x0E, 0x0A, 0x0E, 0x00 }, // ?
	{ 0x00, 0x00, 0x0E, 0x08, 0x04, 0x02, 0x02, 0x00 }, // ?
	{ 0x00, 0x00, 0x0E, 0x0A, 0x0E, 0x0A, 0x0E, 0x00 }, // ?
	{ 0x00, 0x00, 0x0E, 0x0A, 0x0E, 0x08, 0x06, 0x00 }, // ?
	{ 0x08, 0x04, 0x0E, 0x11, 0x11, 0x1F, 0x11, 0x00 }, // ?
	{ 0x02, 0x04, 0x0E, 0x11, 0x11, 0x1F, 0x11, 0x00 }, // ?
	{ 0x04, 0x0A, 0x00, 0x0E, 0x11, 0x1F, 0x11, 0x00 }, // ?
	{ 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x1F, 0x11, 0x00 }, // ?
	{ 0x08, 0x04, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00 }, // ?
	{ 0x02, 0x04, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00 }, // ?
	{ 0x04, 0x0A, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00 }, // ?
	{ 0x0A, 0x00, 0x0E, 0x10, 0x1E, 0x11, 0x1E, 0x00 }, // ?
	{ 0x08, 0x04, 0x1F, 0x01, 0x0F, 0x01, 0x1F, 0x00 }, // ?
	{ 0x02, 0x04, 0x1F, 0x01, 0x0F, 0x01, 0x1F, 0x00 }, // ?
	{ 0x04, 0x0A, 0x1F, 0x01, 0x0F, 0x01, 0x1F, 0x00 }, // ?
	{ 0x0A, 0x00, 0x1F, 0x01, 0x0F, 0x01, 0x1F, 0x00 }, // ?
	{ 0x08, 0x04, 0x0E, 0x11, 0x1F, 0x01, 0x0E, 0x00 }, // ?
	{ 0x02, 0x04, 0x0E, 0x11, 0x1F, 0x01, 0x0E, 0x00 }, // ?
	{ 0x04, 0x0A, 0x0E, 0x11, 0x1F, 0x01, 0x0E, 0x00 }, // ?
	{ 0x0A, 0x00, 0x0E, 0x11, 0x1F, 0x01, 0x0E, 0x00 }, // ?
	{ 0x08, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // ?
	{ 0x02, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // ?
	{ 0x04, 0x0A, 0x0E, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // ?
	{ 0x0A, 0x00, 0x0E, 0x04, 0x04, 0x04, 0x0E, 0x00 }, // ?
	{ 0x08, 0x04, 0x00, 0x06, 0x04, 0x04, 0x0E, 0x00 }, // ?
	{ 0x02, 0x04, 0x00, 0x06, 0x04, 0x04, 0x0E, 0x00 }, // ?
	{ 0x04, 0x0A, 0x00, 0x06, 0x04, 0x04, 0x0E, 0x00 }, //
	{ 0x0A, 0x00, 0x00, 0x06, 0x04, 0x04, 0x0E, 0x00 }, // ¡
	{ 0x08, 0x04, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // ¢
	{ 0x02, 0x04, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // £
	{ 0x04, 0x0A, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // ¤
	{ 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // ¥
	{ 0x08, 0x04, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00 }, // ¦
	{ 0x02, 0x04, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00 }, // §
	{ 0x04, 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00 }, // ¨
	{ 0x0A, 0x00, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00 }, // ©
	{ 0x08, 0x04, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // ª
	{ 0x02, 0x04, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // «
	{ 0x04, 0x0A, 0x00, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // ¬
	{ 0x0A, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00 }, // ­
	{ 0x08, 0x04, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00 }, // ®
	{ 0x02, 0x04, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00 }, // ¯
	{ 0x04, 0x0A, 0x00, 0x11, 0x11, 0x19, 0x16, 0x00 }, // °
	{ 0x0A, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00 }, // ±
	{ 0x0E, 0x11, 0x01, 0x11, 0x0E, 0x04, 0x07, 0x00 }, // ²
	{ 0x00, 0x00, 0x0E, 0x01, 0x11, 0x0E, 0x07, 0x00 }, // ³
	{ 0x14, 0x0A, 0x11, 0x13, 0x15, 0x19, 0x11, 0x00 }, // ´
	{ 0x14, 0x0A, 0x00, 0x0D, 0x13, 0x11, 0x11, 0x00 }, // µ
	{ 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ¶
	{ 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ·
	{ 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ¸
	{ 0x04, 0x00, 0x04, 0x02, 0x01, 0x11, 0x0E, 0x00 }, // ¹
	{ 0x04, 0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x00 }, // º
	{ 0x00, 0x00, 0x16, 0x09, 0x09, 0x09, 0x16, 0x00 }, // »
	{ 0x0C, 0x12, 0x12, 0x0E, 0x12, 0x12, 0x0D, 0x00 }, // ¼
	{ 0x00, 0x00, 0x12, 0x15, 0x08, 0x08, 0x08, 0x00 }, // ½
	{ 0x00, 0x00, 0x00, 0x04, 0x0A, 0x11, 0x1F, 0x00 }, // ¾
	{ 0x0C, 0x02, 0x04, 0x08, 0x1E, 0x11, 0x0E, 0x00 }, // ¿
	{ 0x00, 0x00, 0x0E, 0x01, 0x0F, 0x01, 0x0E, 0x00 }, // À
	{ 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x00 }, // Á
	{ 0x00, 0x02, 0x04, 0x08, 0x0C, 0x12, 0x11, 0x00 }, // Â
	{ 0x00, 0x00, 0x09, 0x09, 0x09, 0x17, 0x01, 0x00 }, // Ã
	{ 0x00, 0x00, 0x1F, 0x0A, 0x0A, 0x0A, 0x19, 0x00 }, // Ä
	{ 0x00, 0x0C, 0x12, 0x12, 0x0E, 0x02, 0x01, 0x00 }, // Å
	{ 0x1F, 0x02, 0x04, 0x08, 0x04, 0x02, 0x1F, 0x00 }, // Æ
	{ 0x00, 0x00, 0x1E, 0x09, 0x09, 0x09, 0x06, 0x00 }, // Ç
	{ 0x00, 0x00, 0x1E, 0x05, 0x04, 0x14, 0x08, 0x00 }, // È
	{ 0x04, 0x04, 0x0E, 0x15, 0x0E, 0x04, 0x04, 0x00 }, // É
	{ 0x0E, 0x11, 0x11, 0x11, 0x0A, 0x0A, 0x1B, 0x00 }, // Ê
	{ 0x1F, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00 }, // Ë
	{ 0x1F, 0x00, 0x11, 0x11, 0x1E, 0x10, 0x0E, 0x00 }, // Ì
	{ 0x14, 0x08, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Í
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00 }, // Î
	{ 0x00, 0x08, 0x0C, 0x0E, 0x0C, 0x08, 0x00, 0x00 }, // Ï
	{ 0x00, 0x00, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00 }, // Ð
	{ 0x08, 0x08, 0x08, 0x04, 0x02, 0x02, 0x02, 0x00 }, // Ñ
	{ 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00 }, // Ò
	{ 0x0E, 0x08, 0x0E, 0x02, 0x0E, 0x00, 0x00, 0x00 }, // Ó
	{ 0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Ô
	{ 0x06, 0x08, 0x04, 0x08, 0x06, 0x00, 0x00, 0x00 }, // Õ
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Ö
	{ 0x02, 0x00, 0x03, 0x02, 0x02, 0x0A, 0x04, 0x00 }, // ×
	{ 0x04, 0x0A, 0x0F, 0x11, 0x0F, 0x01, 0x01, 0x00 }, // Ø
	{ 0x01, 0x12, 0x0A, 0x04, 0x0A, 0x09, 0x10, 0x00 }, // Ù
	{ 0x1F, 0x11, 0x05, 0x07, 0x05, 0x01, 0x01, 0x00 }, // Ú
	{ 0x00, 0x00, 0x0E, 0x11, 0x0F, 0x01, 0x06, 0x00 }, // Û
	{ 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x1C, 0x00 }, // Ü
	{ 0x11, 0x13, 0x17, 0x1F, 0x1D, 0x19, 0x11, 0x00 }, // Ý
	{ 0x05, 0x0A, 0x14, 0x14, 0x14, 0x0A, 0x05, 0x00 }, // Þ
	{ 0x00, 0x02, 0x07, 0x0F, 0x07, 0x02, 0x00, 0x00 }, // ß
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00 }, // à
	{ 0x1F, 0x1B, 0x11, 0x0A, 0x1B, 0x1B, 0x1B, 0x00 }, // á
	{ 0x1F, 0x1B, 0x15, 0x11, 0x15, 0x15, 0x1F, 0x00 }, // â
	{ 0x1F, 0x1B, 0x17, 0x13, 0x15, 0x13, 0x1F, 0x00 }, // ã
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00 }, // ä
	{ 0x04, 0x0E, 0x15, 0x04, 0x04, 0x00, 0x1F, 0x00 }, // å
	{ 0x04, 0x0A, 0x0E, 0x0A, 0x0A, 0x00, 0x1F, 0x00 }, // æ
	{ 0x04, 0x08, 0x0C, 0x0A, 0x0C, 0x00, 0x1F, 0x00 }, // ç
	{ 0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00 }, // è
	{ 0x03, 0x07, 0x0E, 0x1C, 0x18, 0x10, 0x00, 0x00 }, // é
	{ 0x1F, 0x1E, 0x1C, 0x18, 0x10, 0x00, 0x00, 0x00 }, // ê
	{ 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x00 }, // ë
	{ 0x00, 0x08, 0x14, 0x17, 0x14, 0x08, 0x00, 0x00 }, // ì
	{ 0x00, 0x04, 0x0A, 0x0A, 0x0A, 0x04, 0x00, 0x00 }, // í
	{ 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00 }, // î
	{ 0x04, 0x0E, 0x1F, 0x0E, 0x0E, 0x0E, 0x00, 0x00 }, // ï
	{ 0x00, 0x0E, 0x0E, 0x0E, 0x1F, 0x0E, 0x04, 0x00 }, // ð
	{ 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x00 }, // ñ
	{ 0x04, 0x1E, 0x05, 0x0E, 0x14, 0x0F, 0x04, 0x00 }, // ò
	{ 0x04, 0x0E, 0x1F, 0x0E, 0x0E, 0x00, 0x00, 0x00 }, // ó
	{ 0x06, 0x09, 0x09, 0x0D, 0x11, 0x11, 0x0D, 0x00 }, // ô
	{ 0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x1F, 0x00 }, // õ
	{ 0x00, 0x10, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00 }, // ö
	{ 0x15, 0x00, 0x11, 0x00, 0x11, 0x00, 0x15, 0x00 }, // ÷
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ø
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ù
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ú
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // û
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ü
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ý
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // þ
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } // ÿ
};
