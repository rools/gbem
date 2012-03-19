#include "gb_machine.h"
#include "gb_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

gb_machine_type gb_machine;

void gb_machine_init() {
	gb_machine.mem = malloc(0x10000);
	gb_machine.rom = NULL;
}

void gb_machine_reset() {
	gb_machine.AF = 0x01B0;
	gb_machine.BC = 0x0013;
	gb_machine.DE = 0x00D8;
	gb_machine.HL = 0x014D;
	gb_machine.PC = 0x0100;
	gb_machine.SP = 0xFFFE;

	gb_machine.mem[0xFF05] = 0x00;
	gb_machine.mem[0xFF06] = 0x00;
	gb_machine.mem[0xFF07] = 0x00;
	gb_machine.mem[0xFF10] = 0x80;
	gb_machine.mem[0xFF11] = 0xBF;
	gb_machine.mem[0xFF12] = 0xF3;
	gb_machine.mem[0xFF14] = 0xBF;
	gb_machine.mem[0xFF16] = 0x3F;
	gb_machine.mem[0xFF17] = 0x00;
	gb_machine.mem[0xFF19] = 0xBF;
	gb_machine.mem[0xFF1A] = 0x7F;
	gb_machine.mem[0xFF1B] = 0xFF;
	gb_machine.mem[0xFF1C] = 0x9F;
	gb_machine.mem[0xFF1E] = 0xBF;
	gb_machine.mem[0xFF20] = 0xFF;
	gb_machine.mem[0xFF21] = 0x00;
	gb_machine.mem[0xFF22] = 0x00;
	gb_machine.mem[0xFF23] = 0xBF;
	gb_machine.mem[0xFF24] = 0x77;
	gb_machine.mem[0xFF25] = 0xF3;
	gb_machine.mem[0xFF26] = 0xF1;
	gb_machine.mem[0xFF40] = 0x91;
	gb_machine.mem[0xFF42] = 0x00;
	gb_machine.mem[0xFF43] = 0x00;
	gb_machine.mem[0xFF45] = 0x00;
	gb_machine.mem[0xFF47] = 0xFC;
	gb_machine.mem[0xFF48] = 0xFF;
	gb_machine.mem[0xFF49] = 0xFF;
	gb_machine.mem[0xFF4A] = 0x00;
	gb_machine.mem[0xFF4B] = 0x00;
	gb_machine.mem[0xFFFF] = 0x00;
}

gb_error gb_machine_load_rom(const char *path) {
	FILE *file;
	int rom_size;

	free(gb_machine.rom);

	file = fopen(path, "r");

	if (!file)
		return GB_ERROR_CANT_OPEN_FILE;

	/* Determine ROM file size. */
	fseek(file, 0, SEEK_END);
	rom_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	/* Load ROM. */
	gb_machine.rom = malloc(rom_size);
	fread(gb_machine.rom, 1, rom_size, file);
	fclose(file);

	/* Copy ROM bank #0 to memory. */
	memcpy(gb_machine.mem, gb_machine.rom, 0x4000);

	return GB_ERROR_OK;	
}
