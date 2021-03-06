/* by CYB(cybcaoyibo@126.com) */

#include <stdint.h>
#include <math.h>
#include <malloc.h>

//lcd size = 240*160
//buffer size = 256*256
//map offset = 0x4000
//tile offset = 0x0000
//stack bottom = 0x03007F00

extern uint8_t smfdog_palette[];
extern uint8_t smfdog_tile[];
extern uint8_t smfdog_palette_size;

void install_smfdog_palette() {
	uint32_t i;
	for(i = 0; i < smfdog_palette_size; i++) {
		((uint16_t*)0x05000200)[i + 1] = ((uint16_t*)smfdog_palette)[i];
	}
}

void install_smfdog_tile() {
	uint32_t *ptr = (uint32_t*)0x06010000;
	uint16_t y, x, i;
	for(y = 0; y < 8; y++) {
		for(x = 0; x < 8; x++) {
			for(i = 0; i < 8; i++) {
				uint32_t *ptr_src = (uint32_t*)smfdog_tile + ((y * 8 + i) * 64 + x * 8) / 4;
				*(ptr++) = *(ptr_src++);
				*(ptr++) = *(ptr_src++);
			}
		}
	}
}

void install_smfdog_obj(int16_t x, int8_t y, uint8_t facing) {
	*(uint16_t*)0x07000000 = 0x2000 | y;
	*(uint16_t*)0x07000002 = 0xC000 | (x & 0x1FF) | (facing ? (1 << 12) : 0);
	*(uint16_t*)0x07000004 = 0x0000;
}

void init_lcd() {
	//mode 0, bg 3, obj, one dimension obj tile
	*(uint16_t*)0x04000000 = 0x1840;
	//bg3 setting (priority=3)
	*(uint16_t*)0x0400000E = 0x0883;
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
	install_smfdog_tile(2);
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
	//smfdog
	install_smfdog_palette();
	install_smfdog_tile();
}

void init_irq() {
	*(uint16_t*)0x04000004 = 0x0008;
	*(uint16_t*)0x04000200 = 0x0001;
}

uint8_t irq_fired;

void irq_handler() {
	if(*(volatile uint16_t*)0x04000202 & 0x0001) {
		irq_fired = 1;
		*(uint32_t*)0x04000208 = 0;
		*(uint32_t*)0x03007FF8 |= 0x0001;
		*(uint16_t*)0x04000202 = 0x0001;
	}
}

void wait();
float x, y, vx, vy;
uint8_t facing;

void entry_c() {
	init_lcd();
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	facing = 0;
	init_irq();
	while(1) {
		irq_fired = 0;
		wait();
		if(irq_fired == 1) {
			uint16_t key = *(volatile uint16_t*)0x04000130;
			
			x += vx;
			y += vy;
			
			vy += 0.1;
			if(y >= 160 - 64) {
				y = 160 - 64;
				vy = 0;
				if(!(key & (1 << 0)) || !(key & (1 << 1)))
					vy = -3;
			}
			
			if(!(key & (1 << 5)))
				vx -= 0.2;
			if(!(key & (1 << 4)))
				vx += 0.2;
			if(vx < -5)
				vx = -5;
			if(vx > 5)
				vx = 5;
			if(x < 0) {
				x = 0;
				vx = 0;
			}
			if(x > 240 - 64) {
				x = 240 - 64;
				vx = 0;
			}
			if(vx > 1)
				facing = 0;
			if(vx < -1)
				facing = 1;
			
			vx *= 0.95;
			
			install_smfdog_obj(x, y, facing);
		}
	}
}
