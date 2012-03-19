#ifndef GB_MACHINE_H
#define GB_MACHINE_H

#include "gb_types.h"

/* Structure containing the enitre state of a machine. */
typedef struct {
	/* CPU registers. */
	unsigned int AF;
	unsigned int BC;
	unsigned int DE;
	unsigned int HL;
	unsigned int PC; /* Program counter */
	unsigned int SP; /* Stack pointer */

	/* Flag registers. */
	int flag_Z; /* Zero flag */
	int flag_N; /* Subtract flag */
	int flag_H; /* Half carry flag */
	int flag_C; /* Carry flag */

	/* Emulator memory. */
	unsigned char *mem;
	unsigned char *rom;

	gb_bool interrupts_enabled;
	gb_bool ram_bank_enabled;
	gb_memory_mode memory_mode;

	int rom_bank; /* Selected ROM bank */
	int ram_bank; /* Selected RAM bank */
} gb_machine_type;

void gb_machine_init();
void gb_machine_reset();
gb_error gb_machine_load_rom(const char *path);

#endif
