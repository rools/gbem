#include "gb_cpu.h"
#include "gb_machine.h"
#include "gb_mem.h"
#include "gb_cpu_instruction_cycles.h"

#include <stdio.h>
#include <stdlib.h>

extern gb_machine_type gb_machine;

/* Accessors for 8-bit CPU registers. */
inline unsigned int gb_get_A() { return gb_machine.AF >> 8; }
inline unsigned int gb_get_B() { return gb_machine.BC >> 8; }
inline unsigned int gb_get_C() { return gb_machine.BC & 0xFF; }
inline unsigned int gb_get_D() { return gb_machine.DE >> 8; }
inline unsigned int gb_get_E() { return gb_machine.DE & 0xFF; }
inline unsigned int gb_get_F() { return gb_machine.AF & 0xFF; }
inline unsigned int gb_get_H() { return gb_machine.HL >> 8; }
inline unsigned int gb_get_L() { return gb_machine.HL & 0xFF; }

/* Mutators for 8-bit CPU registers. */
inline void gb_set_A(unsigned int n) { gb_machine.AF = (gb_machine.AF & 0xFF) | (n << 8); }
inline void gb_set_B(unsigned int n) { gb_machine.BC = (gb_machine.BC & 0xFF) | (n << 8); }
inline void gb_set_C(unsigned int n) { gb_machine.BC = (gb_machine.BC & 0xFF00) | n; }
inline void gb_set_D(unsigned int n) { gb_machine.DE = (gb_machine.DE & 0xFF) | (n << 8); }
inline void gb_set_E(unsigned int n) { gb_machine.DE = (gb_machine.DE & 0xFF00) | n; }
inline void gb_set_F(unsigned int n) { gb_machine.AF = (gb_machine.AF & 0xFF00) | n; }
inline void gb_set_H(unsigned int n) { gb_machine.HL = (gb_machine.HL & 0xFF) | (n << 8); }
inline void gb_set_L(unsigned int n) { gb_machine.HL = (gb_machine.HL & 0xFF00) | n; }

inline unsigned int gb_add(unsigned int a, unsigned int b) {
	unsigned int r = a + b;

	gb_machine.flag_Z = r == 0 ? 1 : 0;
	gb_machine.flag_N = 0;
	gb_machine.flag_H = (((a & 0xF) + (b & 0xF)) & 0x10) == 0 ? 0 : 1;
	gb_machine.flag_C = (r & 0x100) == 0 ? 0 : 1;

	return r & 0xFF;
}

inline unsigned int gb_sub(unsigned int a, unsigned int b) {
	unsigned int r = (a - b) & 0xFF;

	gb_machine.flag_Z = r == 0 ? 1 : 0;
	gb_machine.flag_N = 1;
	gb_machine.flag_H = (a & 0xF) < (b & 0xF) ? 0 : 1;
	gb_machine.flag_C = a < b ? 0 : 1;

	return r;
}

inline unsigned int gb_and(unsigned int a, unsigned int b) {
	unsigned int r = a & b;

	gb_machine.flag_Z = r == 0 ? 1 : 0;
	gb_machine.flag_N = 0;
	gb_machine.flag_H = 1;
	gb_machine.flag_C = 0;

	return r;
}

inline unsigned int gb_or(unsigned int a, unsigned int b) {
	unsigned int r = a | b;

	gb_machine.flag_Z = r == 0 ? 1 : 0;
	gb_machine.flag_N = 0;
	gb_machine.flag_H = 0;
	gb_machine.flag_C = 0;

	return r;
}

inline unsigned int gb_xor(unsigned int a, unsigned int b) {
	unsigned int r = a ^ b;

	gb_machine.flag_Z = r == 0 ? 1 : 0;
	gb_machine.flag_N = 0;
	gb_machine.flag_H = 0;
	gb_machine.flag_C = 0;

	return r;
}

inline unsigned int gb_add_16(unsigned int a, unsigned int b) {
	unsigned int r = a + b;

	gb_machine.flag_N = 0;
	gb_machine.flag_H = r & 0x1000 ? 1 : 0;
	gb_machine.flag_C = r & 0x10000 ? 1 : 0;

	return r & 0xFFFF;
}

/* Swap upper & lower nibbles of n. */
unsigned int gb_swap_nibbles(unsigned int n) {
	gb_machine.flag_Z = n == 0 ? 1 : 0;
	gb_machine.flag_N = 0;
	gb_machine.flag_H = 0;
	gb_machine.flag_C = 0;

	return ((n & 0x0F) << 4) | ((n & 0xF0) >> 4);
}

unsigned int gb_sla(unsigned int n) {
	unsigned int r = n << 1;

	gb_machine.flag_N = 0;
	gb_machine.flag_H = 0;
	gb_machine.flag_C = (r & 0x100) >> 8;

	r &= 0xFF;

	gb_machine.flag_Z = r == 0 ? 1 : 0;

	return r;
}

/* Decimal adjust register A. */
inline void gb_daa() {
	unsigned int hi = gb_get_A() & 0xF0;
	unsigned int lo = gb_get_A() & 0x0F;

	if (gb_machine.flag_N == 0) {
		if (gb_machine.flag_C == 0) {
			if (gb_machine.flag_H == 0) {
				if (hi <= 0x8 && lo >= 0xA && lo <= 0xF) {
					gb_set_A(gb_get_A() + 0x06);
				} else if (hi >= 0xA && hi <= 0xF && lo <= 0x9) {
					gb_set_A(gb_get_A() + 0x60);
					gb_machine.flag_C = 1;
				} else if (hi >= 0x9 && hi <= 0xF && lo >= 0xA && lo <= 0xF) {
					gb_set_A(gb_get_A() + 0x66);
					gb_machine.flag_C = 1;
				}
			} else {
				if (hi <= 0x9 && lo <= 0x3) {
					gb_set_A(gb_get_A() + 0x06);
				} else if (hi >= 0xA && hi <= 0xF && lo <= 0x3) {
					gb_set_A(gb_get_A() + 0x66);
					gb_machine.flag_C = 1;
				}
			}
		} else {
			if (gb_machine.flag_H == 0) {
				if (hi <= 0x2 && lo <= 0x9) {
					gb_set_A(gb_get_A() + 0x60);
				} else if (hi <= 0x2 && lo >= 0xA && lo <= 0xF) {
					gb_set_A(gb_get_A() + 0x66);
				}
			} else if (hi <= 0x3 && lo <= 0x3) {
				gb_set_A(gb_get_A() + 0x66);
			}
		}
	} else {
		if (gb_machine.flag_C == 0) {
			if (gb_machine.flag_H == 1 && hi <= 0x8 && lo >= 0x6 && lo <= 0xF) {
				gb_set_A(gb_get_A() + 0xFA);
			}
		} else {
			if (gb_machine.flag_H == 0 && hi >= 0x7 && hi <= 0xF && lo <= 0x9) {
				gb_set_A(gb_get_A() + 0xA0);
			} else if (gb_machine.flag_H == 1 && hi >= 0x6 && hi <= 0x7 && lo >= 0x6 && lo <= 0xF) {
				gb_set_A(gb_get_A() + 0x9A);
			}
		}
	}

	gb_machine.flag_Z = gb_get_A() == 0 ? 1 : 0;
	gb_machine.flag_H = 0;
}

void gb_cb() {
	int cmd = gb_mem_get(gb_machine.PC);
	int reg = cmd & 0x7;

	if ((cmd & 0xC0) == 0x80) { /* RES */
		int bit = (cmd & 0x38) >> 3;

		switch (reg) {
			case 0x0:
				gb_set_B(gb_get_B() & (~(1 << bit)));
				break;
			case 0x1:
				gb_set_C(gb_get_C() & (~(1 << bit)));
				break;
			case 0x2:
				gb_set_D(gb_get_D() & (~(1 << bit)));
				break;
			case 0x3:
				gb_set_E(gb_get_E() & (~(1 << bit)));
				break;
			case 0x4:
				gb_set_H(gb_get_H() & (~(1 << bit)));
				break;
			case 0x5:
				gb_set_L(gb_get_L() & (~(1 << bit)));
				break;
			case 0x6:
				gb_mem_set(gb_machine.HL, gb_mem_get(gb_machine.HL) & (~(1 << bit)));
				break;
			case 0x7:
				gb_set_A(gb_get_A() & (~(1 << bit)));
				break;
		}
	} else if ((cmd & 0xF8) == 0x30) { /* SWAP */
		switch (reg) {
			case 0x0:
				gb_set_B(gb_swap_nibbles(gb_get_B()));
				break;
			case 0x1:
				gb_set_C(gb_swap_nibbles(gb_get_C()));
				break;
			case 0x2:
				gb_set_D(gb_swap_nibbles(gb_get_D()));
				break;
			case 0x3:
				gb_set_E(gb_swap_nibbles(gb_get_E()));
				break;
			case 0x4:
				gb_set_H(gb_swap_nibbles(gb_get_H()));
				break;
			case 0x5:
				gb_set_L(gb_swap_nibbles(gb_get_L()));
				break;
			case 0x6:
				gb_mem_set(gb_machine.HL, gb_swap_nibbles(gb_mem_get(gb_machine.HL)));
				break;
			case 0x7:
				gb_set_A(gb_swap_nibbles(gb_get_A()));
				break;
		}
	} else if ((cmd & 0xC0) == 0x40) { /* BIT */
		int bit = (cmd & 0x38) >> 3;

		gb_machine.flag_H = 1;
		gb_machine.flag_N = 0;

		switch (reg) {
			case 0x0:
				gb_machine.flag_Z = (gb_get_B() >> bit) & 1;
				break;
			case 0x1:
				gb_machine.flag_Z = (gb_get_C() >> bit) & 1;
				break;
			case 0x2:
				gb_machine.flag_Z = (gb_get_D() >> bit) & 1;
				break;
			case 0x3:
				gb_machine.flag_Z = (gb_get_E() >> bit) & 1;
				break;
			case 0x4:
				gb_machine.flag_Z = (gb_get_H() >> bit) & 1;
				break;
			case 0x5:
				gb_machine.flag_Z = (gb_get_L() >> bit) & 1;
				break;
			case 0x6:
				gb_machine.flag_Z = (gb_mem_get(gb_machine.HL) >> bit) & 1;
				break;
			case 0x7:
				gb_machine.flag_Z = (gb_get_A() >> bit) & 1;
				break;
		}
	} else if ((cmd & 0xC0) == 0xC0) { /* SET */
		int bit = (cmd & 0x38) >> 3;

		switch (reg) {
			case 0x0:
				gb_set_B(gb_get_B() | (1 << bit));
				break;
			case 0x1:
				gb_set_C(gb_get_C() | (1 << bit));
				break;
			case 0x2:
				gb_set_D(gb_get_D() | (1 << bit));
				break;
			case 0x3:
				gb_set_E(gb_get_E() | (1 << bit));
				break;
			case 0x4:
				gb_set_H(gb_get_H() | (1 << bit));
				break;
			case 0x5:
				gb_set_L(gb_get_L() | (1 << bit));
				break;
			case 0x6:
				gb_mem_set(gb_machine.HL, gb_mem_get(gb_machine.HL) | (1 << bit));
				break;
			case 0x7:
				gb_set_A(gb_get_A() | (1 << bit));
				break;
		}
	} else if ((cmd & 0xF8) == 0x20) { /* SLA */
		switch (reg) {
			case 0x0:
				gb_set_B(gb_sla(gb_get_B()));
				break;
			case 0x1:
				gb_set_C(gb_sla(gb_get_C()));
				break;
			case 0x2:
				gb_set_D(gb_sla(gb_get_D()));
				break;
			case 0x3:
				gb_set_E(gb_sla(gb_get_E()));
				break;
			case 0x4:
				gb_set_H(gb_sla(gb_get_H()));
				break;
			case 0x5:
				gb_set_L(gb_sla(gb_get_L()));
				break;
			case 0x6:
				gb_mem_set(gb_machine.HL, gb_sla(gb_mem_get(gb_machine.HL)));
				break;
			case 0x7:
				gb_set_A(gb_sla(gb_get_A()));
				break;
		}
	} else {
		fprintf(stderr, "CB %02X not implemented\n", cmd);
		exit(1);
	}

	++gb_machine.PC;
}

void gb_cpu_run(int cycles) {
	while (cycles > 0) {
		int opcode = gb_mem_get(gb_machine.PC);

		// TODO: Remove +1 when all instruction cycle counts are in the table.
		cycles -= GB_CPU_INSTRUCTION_CYCLES[opcode] + 1;

		printf("inst 0x%02X at 0x%04X\n", opcode, gb_machine.PC);
		
		gb_mem_set(0xFF00, 0x28);

		switch (opcode) {
			case 0x00: /* NOP */
				++gb_machine.PC;
				break;

			case 0x01: /* LD */
				gb_machine.BC = gb_mem_get_16(gb_machine.PC + 1);
				gb_machine.PC += 3;
				break;

			case 0x02: /*LD */
				gb_mem_set(gb_machine.BC, gb_get_A());
				++gb_machine.PC;
				break;

			case 0x03: /* INC */
				gb_machine.BC = (gb_machine.BC + 1) & 0xFFFF;
				++gb_machine.PC;
				break;

			case 0x04: /* INC */
				gb_set_B(gb_add(gb_get_B(), 1));
				++gb_machine.PC;
				break;

			case 0x05: /* DEC */
				gb_set_B(gb_sub(gb_get_B(), 1));
				printf("B:%i\n", gb_get_B());
				++gb_machine.PC;
				break;

			case 0x06: /* LD */
				gb_set_B(gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;

			case 0x07: { /* RLCA */
				int A = gb_get_A();
		
				gb_machine.flag_N = 0;
				gb_machine.flag_H = 0;
				gb_machine.flag_C = (A & 0x80) == 0 ? 0 : 1;
		
				A = ((A << 1) & 0xFF) | gb_machine.flag_C;
		
				gb_machine.flag_Z = A == 0 ? 1 : 0;
		
				gb_set_A(A);
		
				++gb_machine.PC;
		
				break;	
			}
		
			case 0x08: /* LD */
				gb_mem_set_16(gb_mem_get_16(gb_machine.PC + 1), gb_machine.SP);
				gb_machine.PC += 3;
				break;
		
			case 0x09: /* ADD */
				gb_machine.HL = gb_add_16(gb_machine.BC, gb_machine.HL);
				++gb_machine.PC;
				break;
		
			case 0x0B: /* DEC */
				gb_machine.BC = (gb_machine.BC - 1) & 0xFFFF;
				++gb_machine.PC;
				break;
		
			case 0x0C: /* INC */
				gb_set_C(gb_add(gb_get_C(), 1));
				++gb_machine.PC;
				break;
		
			case 0x0D: /* DEC */
				gb_set_C(gb_sub(gb_get_C(), 1));
				printf("C:%i\n", gb_get_C());

				++gb_machine.PC;
				break;
		
			case 0x0E: /* LD */
				gb_set_C(gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
		
			case 0x10: /* STOP */
				// TODO: implement.
				++gb_machine.PC;
				break;
		
			case 0x11: /* LD */
				gb_machine.DE = gb_mem_get_16(gb_machine.PC + 1);
				gb_machine.PC += 3;
				break;
		
			case 0x12: /* LD */
				gb_mem_set(gb_machine.DE, gb_get_A());
				++gb_machine.PC;
				break;
		
			case 0x13: /* INC */
				gb_machine.DE = (gb_machine.DE + 1) & 0xFFFF;
				++gb_machine.PC;
				break;

			case 0x15: /* DEC */
				gb_set_D(gb_sub(gb_get_D(), 1));
				++gb_machine.PC;
				break;

			case 0x16: /* LD */
				gb_set_D(gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
		
			case 0x18: /* JR */
				gb_machine.PC += gb_mem_get_signed(gb_machine.PC + 1) + 2;
				break;
		
			case 0x19: /* ADD */
				gb_machine.HL = gb_add_16(gb_machine.HL, gb_machine.DE);
				++gb_machine.PC;
				break;
		
			case 0x1A: /* LD */
				gb_set_A(gb_mem_get(gb_machine.DE));
				++gb_machine.PC;
				break;
		
			case 0x1C: /* INC */
				gb_set_E(gb_add(gb_get_E(), 1));
				++gb_machine.PC;
				break;
		
			case 0x1F: { /* RRA */
				int A = (gb_get_A() | (gb_machine.flag_C << 8)) >> 1;
		
				gb_machine.flag_Z = A == 0 ? 1 : 0;
				gb_machine.flag_N = 0;
				gb_machine.flag_H = 0;
				gb_machine.flag_C = gb_get_A() & 0x1;

				gb_set_A(A);

				++gb_machine.PC;
		
				break;
			}
		
			case 0x20: /* JR */
				gb_machine.PC += 2;
				if (gb_machine.flag_Z == 0)
					gb_machine.PC += gb_mem_get_signed(gb_machine.PC - 1);
				break;
		
			case 0x21: /* LD */
				gb_machine.HL = gb_mem_get_16(gb_machine.PC + 1);
				gb_machine.PC += 3;
				break;
		
			case 0x22: /* LDI */
				gb_mem_set(gb_machine.HL, gb_get_A());
				gb_machine.HL = (gb_machine.HL + 1) & 0xFFFF;
				++gb_machine.PC;
				break;
		
			case 0x23: /* INC */
				gb_machine.HL = (gb_machine.HL + 1) & 0xFFFF;
				++gb_machine.PC;
				break;

			case 0x26: /* LD */
				gb_set_H(gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
		
			case 0x27: /* DAA */
				gb_daa();
				++gb_machine.PC;
				break;
		
			case 0x28: /* JR */
				gb_machine.PC += 2;
				if (gb_machine.flag_Z == 1)
					gb_machine.PC += gb_mem_get_signed(gb_machine.PC - 1);
				break;
		
			case 0x2A: /* LDI */
				gb_set_A(gb_mem_get(gb_machine.HL));
				gb_machine.HL = (gb_machine.HL + 1) & 0xFFFF;
				++gb_machine.PC;
				break;
		
			case 0x2C: /* INC */
				gb_set_L(gb_add(gb_get_L(), 1));
				++gb_machine.PC;
				break;
		
			case 0x2D: /* DEC */
				gb_set_L(gb_sub(gb_get_L(), 1));
				++gb_machine.PC;
				break;
		
			case 0x2E: /* LD */
				gb_set_L(gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
		
			case 0x2F: /* CPL */
				gb_set_A((~gb_get_A()) & 0xFF);
				gb_machine.flag_N = 1;
				gb_machine.flag_H = 1;
				++gb_machine.PC;
				break;

			case 0x30: /* JR */
				gb_machine.PC += 2;
				if (gb_machine.flag_C == 0)
					gb_machine.PC += gb_mem_get_signed(gb_machine.PC - 1);
				break;

			case 0x31: /* LD */
				gb_machine.SP = gb_mem_get_16(gb_machine.PC + 1);
				gb_machine.PC += 3;
				break;
		
			case 0x32: /* LDD */
				gb_mem_set(gb_machine.HL, gb_get_A());
				gb_machine.HL = (gb_machine.HL - 1) & 0xFFFF;
				++gb_machine.PC;
				break;
		
			case 0x34: /* INC */
				gb_mem_set(gb_machine.HL, gb_add(gb_mem_get(gb_machine.HL), 1));
				++gb_machine.PC;
				break;
		
			case 0x35: /* DEC */
				gb_mem_set(gb_machine.HL, gb_sub(gb_mem_get(gb_machine.HL), 1));
				++gb_machine.PC;
				break;
		
			case 0x36: /* LD */
				gb_mem_set(gb_machine.HL, gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
		
			case 0x38: /* JR */
				gb_machine.PC += 2;
				if (gb_machine.flag_C == 1)
					gb_machine.PC += gb_mem_get_signed(gb_machine.PC - 1);
				break;
		
			case 0x3C: /* INC */
				gb_set_A(gb_add(gb_get_A(), 1));
				++gb_machine.PC;
				break;
		
			case 0x3D: /* DEC */
				gb_set_A(gb_sub(gb_get_A(), 1));
				++gb_machine.PC;
				break;
		
			case 0x3E: /* LD */
				gb_set_A(gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
		
			case 0x3F: /* CCF */
				gb_machine.flag_N = 0;
				gb_machine.flag_H = 0;
				gb_machine.flag_C = gb_machine.flag_C == 0 ? 1 : 0;
				++gb_machine.PC;
				break;
		
			case 0x40: /* LD */
				// set_B(get_B());
				++gb_machine.PC;
				break;
		
			case 0x41: /* LD */
				gb_set_B(gb_get_C());
				++gb_machine.PC;
				break;
		
			case 0x42: /* LD */
				gb_set_B(gb_get_D());
				++gb_machine.PC;
				break;
		
			case 0x43: /* LD */
				gb_set_B(gb_get_E());
				++gb_machine.PC;
				break;
		
			case 0x44: /* LD */
				gb_set_B(gb_get_H());
				++gb_machine.PC;
				break;
		
			case 0x45: /* LD */
				gb_set_B(gb_get_L());
				++gb_machine.PC;
				break;
		
			case 0x46: /* LD */
				gb_set_B(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;
		
			case 0x47: /* LD */
				gb_set_B(gb_get_A());
				++gb_machine.PC;
				break;
		
			case 0x4E: /* LD */
				gb_set_C(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;
		
			case 0x4F: /* LD */
				gb_set_C(gb_get_A());
				++gb_machine.PC;
				break;
		
			case 0x56: /* LD */
				gb_set_D(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;
		
			case 0x57: /* LD */
				gb_set_D(gb_get_A());
				++gb_machine.PC;
				break;
		
			case 0x58: /* LD */
				gb_set_E(gb_get_B());
				++gb_machine.PC;
				break;
		
			case 0x59: /* LD */
				gb_set_E(gb_get_C());
				++gb_machine.PC;
				break;
		
			case 0x5A: /* LD */
				gb_set_E(gb_get_D());
				++gb_machine.PC;
				break;
		
			case 0x5B: /* LD */
				gb_set_E(gb_get_E());
				++gb_machine.PC;
				break;
		
			case 0x5C: /* LD */
				gb_set_E(gb_get_H());
				++gb_machine.PC;
				break;
		
			case 0x5D: /* LD */
				gb_set_E(gb_get_L());
				++gb_machine.PC;
				break;
		
			case 0x5E: /* LD */
				gb_set_E(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;
		
			case 0x5F: /* LD */
				gb_set_E(gb_get_A());
				++gb_machine.PC;
				break;
		
			case 0x60: /* LD */
				gb_set_H(gb_get_B());
				++gb_machine.PC;
				break;
		
			case 0x61: /* LD */
				gb_set_H(gb_get_C());
				++gb_machine.PC;
				break;
		
			case 0x62: /* LD */
				gb_set_H(gb_get_D());
				++gb_machine.PC;
				break;
		
			case 0x63: /* LD */
				gb_set_H(gb_get_E());
				++gb_machine.PC;
				break;
		
			case 0x65: /* LD */
				gb_set_H(gb_get_L());
				++gb_machine.PC;
				break;
		
			case 0x66: /* LD */
				gb_set_H(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;

			case 0x67: /* LD */
				gb_set_H(gb_get_A());
				++gb_machine.PC;
				break;

			case 0x68: /* LD */
				gb_set_L(gb_get_B());
				++gb_machine.PC;
				break;
		
			case 0x69: /* LD */
				gb_set_L(gb_get_C());
				++gb_machine.PC;
				break;
		
			case 0x6A: /* LD */
				gb_set_L(gb_get_D());
				++gb_machine.PC;
				break;
		
			case 0x6B: /* LD */
				gb_set_L(gb_get_E());
				++gb_machine.PC;
				break;
		
			case 0x6C: /* LD */
				gb_set_L(gb_get_H());
				++gb_machine.PC;
				break;
		
			case 0x6E: /* LD */
				gb_set_L(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;

			case 0x6F: /* LD */
				gb_set_L(gb_get_A());
				++gb_machine.PC;
				break;

			case 0x70: /* LD */
				gb_mem_set(gb_machine.HL, gb_get_B());
				++gb_machine.PC;
				break;
		
			case 0x74: /* LD */
				gb_mem_set(gb_machine.HL, gb_get_H());
				++gb_machine.PC;
				break;
		
			case 0x76: /* HALT */
				if (gb_machine.interrupts_enabled)
					++gb_machine.PC;
				else
					gb_machine.PC += 2;
				break;
		
			case 0x77: /* LD */
				gb_mem_set(gb_machine.HL, gb_get_A());
				++gb_machine.PC;
				break;
		
			case 0x78: /* LD */
				gb_set_A(gb_get_B());
				++gb_machine.PC;
				break;
		
			case 0x79: /* LD */
				gb_set_A(gb_get_C());
				++gb_machine.PC;
				break;
			
			case 0x7A: /* LD */
				gb_set_A(gb_get_D());
				++gb_machine.PC;
				break;
			
			case 0x7B: /* LD */
				gb_set_A(gb_get_E());
				++gb_machine.PC;
				break;
			
			case 0x7C: /* LD */
				gb_set_A(gb_get_H());
				++gb_machine.PC;
				break;
			
			case 0x7D: /* LD */
				gb_set_A(gb_get_L());
				++gb_machine.PC;
				break;
			
			case 0x7E: /* LD */
				gb_set_A(gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;
			
			case 0x80: /* gb_sub */
				gb_set_A(gb_sub(gb_get_B(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x81: /* gb_sub */
				gb_set_A(gb_sub(gb_get_C(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x82: /* gb_sub */
				gb_set_A(gb_sub(gb_get_D(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x83: /* gb_sub */
				gb_set_A(gb_sub(gb_get_E(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x84: /* gb_sub */
				gb_set_A(gb_sub(gb_get_H(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x85: /* gb_sub */
				gb_set_A(gb_sub(gb_get_L(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x87: /* gb_sub */
				gb_set_A(gb_sub(gb_get_A(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0x88: /* ADC */
				gb_set_A(gb_sub(gb_get_A(), gb_get_B() + gb_machine.flag_C));
				++gb_machine.PC;
				break;

			case 0x95: /* SUB */
				gb_set_A(gb_sub(gb_get_A(), gb_get_L()));
				++gb_machine.PC;
				break;
			
			case 0x9E: /* SBC */
				gb_set_A(gb_sub(gb_get_A(), gb_mem_get(gb_machine.HL) + gb_machine.flag_C));
				++gb_machine.PC;
				break;

			case 0x9F: /* SBC */
				gb_set_A(gb_sub(gb_get_A(), gb_get_A() + gb_machine.flag_C));
				++gb_machine.PC;
				break;

			case 0xA0: /* AND */
				gb_set_A(gb_and(gb_get_B(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA1: /* AND */
				gb_set_A(gb_and(gb_get_C(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA2: /* AND */
				gb_set_A(gb_and(gb_get_D(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA3: /* AND */
				gb_set_A(gb_and(gb_get_E(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA4: /* AND */
				gb_set_A(gb_and(gb_get_H(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA5: /* AND */
				gb_set_A(gb_and(gb_get_L(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA7: /* AND */
				gb_set_A(gb_and(gb_get_A(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA8: /* gb_xor */
				gb_set_A(gb_xor(gb_get_B(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xA9: /* gb_xor */
				gb_set_A(gb_xor(gb_get_C(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xAA: /* gb_xor */
				gb_set_A(gb_xor(gb_get_D(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xAB: /* gb_xor */
				gb_set_A(gb_xor(gb_get_E(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xAC: /* gb_xor */
				gb_set_A(gb_xor(gb_get_H(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xAD: /* gb_xor */
				gb_set_A(gb_xor(gb_get_L(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xAE: /* gb_xor */
				gb_set_A(gb_xor(gb_mem_get(gb_machine.HL), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xAF: /* gb_xor */
				gb_set_A(gb_xor(gb_get_A(),  gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xB0: /* OR */
				gb_set_A(gb_or(gb_get_B(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xB1: /* OR */
				gb_set_A(gb_or(gb_get_C(), gb_get_A()));
				++gb_machine.PC;
				break;
			
			case 0xB2: /* OR */
				gb_set_A(gb_or(gb_get_D(), gb_get_A()));
				++gb_machine.PC;
				break;

			case 0xB4: /* OR */
				gb_set_A(gb_or(gb_get_H(), gb_get_A()));
				++gb_machine.PC;
				break;

			case 0xB7: /* OR */
				gb_set_A(gb_or(gb_get_A(), gb_get_A()));
				++gb_machine.PC;
				break;

			case 0xB8: /* CP */
				gb_sub(gb_get_A(), gb_get_B());
				++gb_machine.PC;
				break;
			
			case 0xB9: /* CP */
				gb_sub(gb_get_A(), gb_get_C());
				++gb_machine.PC;
				break;
			
			case 0xBA: /* CP */
				gb_sub(gb_get_A(), gb_get_D());
				++gb_machine.PC;
				break;
			
			case 0xBB: /* CP */
				gb_sub(gb_get_A(), gb_get_E());
				++gb_machine.PC;
				break;
			
			case 0xBC: /* CP */
				gb_sub(gb_get_A(), gb_get_H());
				++gb_machine.PC;
				break;
			
			case 0xBD: /* CP */
				gb_sub(gb_get_A(), gb_get_L());
				++gb_machine.PC;
				break;
			
			case 0xBE: /* CP */
				gb_sub(gb_get_A(), gb_mem_get(gb_machine.HL));
				++gb_machine.PC;
				break;
			
			case 0xBF: /* BF */
				gb_sub(gb_get_A(), gb_get_A());
				++gb_machine.PC;
				break;
			
			case 0xC0: /* RET */
				if (gb_machine.flag_Z == 0) {
					gb_machine.PC = gb_mem_get_16(gb_machine.SP);
					gb_machine.SP += 2;
				} else
					++gb_machine.PC;
				break;

			case 0xC1: /* POP */
				gb_machine.BC = gb_mem_get_16(gb_machine.SP);
				gb_machine.SP += 2;
				++gb_machine.PC;
				break;

			case 0xC2: /* JP */
				if (gb_machine.flag_Z == 0)
					gb_machine.PC = gb_mem_get_16(gb_machine.PC + 1);
				else
					gb_machine.PC += 3;
				break;

			case 0xC3: /* JP */
				gb_machine.PC = gb_mem_get_16(gb_machine.PC + 1);
				break;
	
			case 0xC4: /* CALL */
				if (gb_machine.flag_Z == 0)
					gb_machine.PC = gb_mem_get_16(gb_machine.PC + 1);
				else
					gb_machine.PC += 3;
				break;
			
			case 0xC5: /* PUSH */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.BC);
				++gb_machine.PC;
				break;

			case 0xC8: /* RET */
				if (gb_machine.flag_Z == 1) {
					gb_machine.PC = gb_mem_get_16(gb_machine.SP);
					gb_machine.SP += 2;
				} else
				++gb_machine.PC;
			break;

			case 0xC9: /* RET */
				gb_machine.PC = gb_mem_get_16(gb_machine.SP);
				gb_machine.SP += 2;
				break;
	
			case 0xCA: /* JP */
				if (gb_machine.flag_Z == 1)
					gb_machine.PC = gb_mem_get_16(gb_machine.PC + 1);
				else
					gb_machine.PC += 3;
				break;
	
			case 0xCB:
				++gb_machine.PC;
				gb_cb();
				cycles -= GB_CPU_INSTRUCTION_CYCLES_CB[opcode];
				break;
			
			case 0xCD: /* CALL */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.PC + 3);
				gb_machine.PC = gb_mem_get_16(gb_machine.PC + 1);
				break;
	
			case 0xD1: /* POP */
				gb_machine.DE = gb_mem_get_16(gb_machine.SP);
				gb_machine.SP += 2;
				++gb_machine.PC;
				break;
			
			case 0xD5: /* PUSH */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.DE);
				++gb_machine.PC;
				break;
			
			case 0xD8: /* RET */
				if (gb_machine.flag_C == 1) {
					gb_machine.PC = gb_mem_get_16(gb_machine.SP);
					gb_machine.SP += 2;
				} else
					++gb_machine.PC;
				break;

			case 0xD9: /* RET */
				gb_machine.PC = gb_mem_get_16(gb_machine.SP);
				gb_machine.SP += 2;
				gb_machine.interrupts_enabled = 1;
				break;

			case 0xDC: /* CALL */
				if (gb_machine.flag_C == 1)
					gb_machine.PC = gb_mem_get_16(gb_machine.PC + 1);
				else
					gb_machine.PC += 3;
				break;
			
			case 0xE0: /* LD */
				gb_mem_set(0xFF00 + gb_mem_get(gb_machine.PC + 1), gb_get_A());
				gb_machine.PC += 2;
				break;
			
			case 0xE1: /* POP */
				gb_machine.HL = gb_mem_get_16(gb_machine.SP);
				gb_machine.SP += 2;
				++gb_machine.PC;
				break;
			
			case 0xE2: /* LD */
				gb_mem_set(0xFF00 + gb_get_C(), gb_get_A());
				++gb_machine.PC;
				break;
			
			case 0xE5: /* PUSH */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.HL);
				++gb_machine.PC;
				break;
			
			case 0xE6: /* AND */
				gb_set_A(gb_and(gb_mem_get(gb_machine.PC + 1), gb_get_A()));
				gb_machine.PC += 2;
				break;
			
			case 0xE9: /* JP */
				gb_machine.PC = gb_machine.HL;
				break;
			
			case 0xEA: /* LD */
				gb_mem_set(gb_mem_get_16(gb_machine.PC + 1), gb_get_A());
				gb_machine.PC += 3;
				break;
			
			case 0xEF: /* RST */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.PC + 1);
				gb_machine.PC = 0x0028;
				break;
			
			case 0xF0: /* LD */
				gb_set_A(gb_mem_get(0xFF00 + gb_mem_get(gb_machine.PC + 1)));
				gb_machine.PC += 2;
				break;
			
			case 0xF1: /* POP */
				gb_machine.AF = gb_mem_get_16(gb_machine.SP);
				gb_machine.SP += 2;
				++gb_machine.PC;
				break;
			
			case 0xF2: /* LD */
				gb_set_A(gb_mem_get(0xFF00 + gb_get_C()));
				++gb_machine.PC;
				break;
			
			case 0xF3: /* DI */
				gb_machine.interrupts_enabled = 0;
				++gb_machine.PC;
				break;
			
			case 0xF5: /* PUSH */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.AF);
				++gb_machine.PC;
				break;
	
			case 0xF8: /* LDHL */
				gb_machine.HL = gb_add_16(gb_machine.SP, gb_mem_get(gb_machine.PC + 1));
			
				gb_machine.flag_Z = 0;
			
				gb_machine.PC += 2;
				break;
			
			case 0xFA: /* LD */
				gb_set_A(gb_mem_get(gb_mem_get_16(gb_machine.PC + 1)));
				gb_machine.PC += 3;
				break;
			
			case 0xFB: /* EI */
				gb_machine.interrupts_enabled = 1;
				++gb_machine.PC;
				break;
			
			case 0xFE: /* CP */
				gb_sub(gb_get_A(), gb_mem_get(gb_machine.PC + 1));
				gb_machine.PC += 2;
				break;
			
			case 0xFF: /* RST */
				gb_machine.SP -= 2;
				gb_mem_set_16(gb_machine.SP, gb_machine.PC + 1);
				gb_machine.PC = 0x0038;
				break;

			default: {
				fprintf(stderr, "Error, unknown instruction 0x%X at 0x%X\n", gb_mem_get(gb_machine.PC) & 0xFF, gb_machine.PC);
				exit(1);
			}
		}
	}
}
