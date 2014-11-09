#include <stdint.h>

//lcd size = 240*160
//buffer size = 256*256

void init_lcd() {
	//mode 0, bg 3
	*(uint16_t*)0x04000000 = 0x0800;
	//bg3 setting
	*(uint16_t*)0x0400000E = 0x0880;
	//test tile
	uint16_t i, j, ind = 0;
	for(i = 0; i < 8; i++) {
		((uint32_t*)0x06000000)[i * 2 + 0] = 0x03020100;
		((uint32_t*)0x06000000)[i * 2 + 1] = 0x07060504;
	}
	ind = 0;
	for(i = 0; i < 8; i++) {
		((uint32_t*)0x06000040)[i * 2 + 0] = 0x08080808;
		((uint32_t*)0x06000040)[i * 2 + 1] = 0x08080808;
	}
	//test palette
	for(i = 0; i < 8; i++) {
		uint8_t tmp = i * 31 / 8;
		((uint16_t*)0x05000000)[i] = 0x001F | (tmp << 5) | (tmp << 10);
	}
	((uint16_t*)0x05000000)[8] = 0x7C00;
	//test map
	ind = 0;
	for(i = 0; i < 32; i++) {
		for(j = 0; j < 32; j++) {
			((uint16_t*)0x06004000)[ind] = (i % 2) ^ (j % 2);
			ind++;
		}
	}
}

void entry_c() {
	init_lcd();
	while(1);
}
