#include "gb_mem.h"
#include "gb_machine.h"

#include <stdio.h>
#include <stdlib.h>

extern gb_machine_type gb_machine;

inline unsigned int gb_mem_get(int offset) {
	/* Switchable ROM bank */
	if (offset >= 0x4000 && offset <= 0x7FFF) {
		offset -= 0x4000;
		printf("accessing switchable rom bank (0x%X => 0x%X)\n", offset + 0x4000, offset + gb_machine.rom_bank * 0x4000);
		return gb_machine.rom[offset + gb_machine.rom_bank * 0x4000];
	}

	return gb_machine.mem[offset];
}

inline int gb_mem_get_signed(int offset) {
	/* Switchable ROM bank */
	if (offset >= 0x4000 && offset <= 0x7FFF) {
		offset -= 0x4000;
		printf("accessing switchable rom bank (0x%X => 0x%X)\n", offset + 0x4000, offset + gb_machine.rom_bank * 0x4000);
		return ((signed char *)gb_machine.mem)[offset + gb_machine.rom_bank * 0x4000];
	}

	return ((signed char *)gb_machine.mem)[offset];
}

inline void gb_mem_set(int offset, unsigned int n) {
	if (offset <= 0x1FFF) {
		/* RAM bank disable/enable. */
		gb_machine.ram_bank_enabled = n == 0x0A ? 1 : 0;
		return;
	} else if (offset <= 0x3FFF) {
		/* Select ROM bank. */
		printf("Chose ROM bank (wrote 0x%02X to 0x%04X)\n", n, offset);
		gb_machine.rom_bank = n == 0 ? 1 : n;
		return;
	}

	/* Select memory mode. */
	if (offset >= 0x6000 && offset <= 0x7FFF) {
		printf("Wrote 0x%02X to 0x%04X\n", n, offset);
		gb_machine.memory_mode = n;
		return;	
	}

	/* Video RAM. */
	/*if (offset >= 0x8000 && offset <= 0xA000) {
		printf("Wrote 0x%02X to video RAM (0x%02X)\n", n, offset);
		//exit(1);	
	}*/

	/* Illegal write to ROM. */
	if (offset < 0x8000) {
		printf("Error, tried to write 0x%02X to ROM (0x%02X)\n", n, offset);
		exit(1);
	}

	if (offset == 0xFF40)
		printf("Wrote %02X to LCDC\n", n);

	gb_machine.mem[offset] = n;
}

inline unsigned int gb_mem_get_16(int offset) {
	return gb_mem_get(offset) | (gb_mem_get(offset + 1) << 8);
}

inline void gb_mem_set_16(int offset, unsigned int n) {
	gb_mem_set(offset, n & 0xFF);
	gb_mem_set(offset + 1, n >> 8);
}
