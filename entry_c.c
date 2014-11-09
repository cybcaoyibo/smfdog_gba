#include <stdint.h>

//240*160

const char test_data[] =
	"                        "
	"    ##  #   #  ####     "
	"   #    #   #  #   #    "
	"  #     #   #  #   #    "
	"  #     #   #  #   #    "
	"  #      # #   #   #    "
	"  #       #    #  #     "
	"  #       #    ###      "
	"  #       #    #  #     "
	"  #       #    #   #    "
	"  #       #    #   #    "
	"  #       #    #   #    "
	"  #       #    #   #    "
	"   #      #    #   #    "
	"    ##    #    ####     "
	"                        ";

void draw_test() {
	uint8_t *vram = (uint8_t*)0x06000000;
	uint8_t x, y;
	for(y = 0; y < 160; y++) {
		for(x = 0; x < 240; x++) {
			if(test_data[y / 10 * 24 + x / 10] != ' ')
				*vram = 2;
			else
				*vram = ((x % 20) < 10) ^ ((y % 20) < 10);
			vram++;
		}
	}
}

void entry_c() {
	draw_test();
	while(1);
}
