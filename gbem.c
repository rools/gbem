#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "gb_machine.h"
#include "gb_cpu.h"
#include "gb_mem.h"
#include "gb_screen.h"

extern gb_machine_type gb_machine;

/* Buffer for rendered screen. */
unsigned char *screen;

void render() {
	unsigned int i;
	/*for (i = 0x8000; i < 0x8FFF; ++i) {
		printf("mem[%04X] = %02X\n", i, mem[i]);
	}*/

	for (i = 0; i < 1024; ++i) {
		unsigned int tile = ((signed char *)gb_machine.mem)[0x9800 + i];
		unsigned int tile_x = i % 32;
		unsigned int tile_y = i / 32;
		unsigned int t;

		//printf("%i ", 16 * tile);

		for (t = 0; t < 64; ++t) {
			unsigned int x = t % 8;
			unsigned int y = t / 8;

			unsigned int pixel = (gb_machine.mem[0x9000 + 16 * tile + y * 2] >> x) & 1;
			pixel |= ((gb_machine.mem[0x9000 + 16 * tile + y * 2 + 1] >> x) & 1) << 1;

			screen[tile_x * 8 + tile_y * 2048 + (7 - x) + y * 256] = pixel * 70;
		}
	}
}

int main(int argc, char *argv[]) {
	int i;

	if (argc != 2) {
		fprintf(stderr, "%s: Specify a ROM file\n", argv[0]);
		return 1;
	}

	gb_machine_init();
	gb_machine_reset();

	if (gb_machine_load_rom(argv[1]) != GB_ERROR_OK) {
		fprintf(stderr, "%s: %s: Could not open file\n", argv[0], argv[1]);
		return 1;
	}

	screen = malloc(256 * 256);

	gb_screen_init();

	for (i = 0; i < 100000; ++i) {
		gb_cpu_run(200);

		gb_mem_set(0xFF44, (gb_mem_get(0xFF44) + 1) % 154);

		gb_mem_set(0xFF00, 0x28);

		if (i % 100 == 0) {
			render();
			gb_screen_draw(screen);
		}
	}

	return 0;	
}
