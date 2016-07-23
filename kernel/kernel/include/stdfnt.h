static uint16_t font[65536][16] ={};
struct fontfile {
	char magic[4];
	uint32_t no_char;
	uint32_t charmap_off; //Should be 0x20
	uint32_t charwidth_off;
	uint32_t chr_off;
	char reserved[12];
}__attribute__((packed));
struct charmap {
	short charnumber;
	char seperator;
}__attribute__((packed));
struct charwidth {
	char width; //either 8 or 16
}__attribute__((packed));
struct CHR8 {
	uint8_t rows[16];
}__attribute__((packed));
struct CHR16 {
	uint16_t rows[16];
}__attribute__((packed));