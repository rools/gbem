#ifndef GB_CPU_H
#define GB_CPU_H

/* Accessors for 8-bit CPU registers. */
unsigned int gb_get_A();
unsigned int gb_get_B();
unsigned int gb_get_C();
unsigned int gb_get_D();
unsigned int gb_get_E();
unsigned int gb_get_F();
unsigned int gb_get_H();
unsigned int gb_get_L();

/* Mutators for 8-bit CPU registers. */
void gb_set_A(unsigned int n);
void gb_set_B(unsigned int n);
void gb_set_C(unsigned int n);
void gb_set_D(unsigned int n);
void gb_set_E(unsigned int n);
void gb_set_F(unsigned int n);
void gb_set_H(unsigned int n);
void gb_set_L(unsigned int n);

/* 8-bit arithmetic. */
unsigned int gb_add(unsigned int a, unsigned int b);
unsigned int gb_sub(unsigned int a, unsigned int b);
unsigned int gb_and(unsigned int a, unsigned int b);
unsigned int gb_or(unsigned int a, unsigned int b);
unsigned int gb_xor(unsigned int a, unsigned int b);

/* 16-bit arithmetic. */
unsigned int gb_add_16(unsigned int a, unsigned int b);

/* Bit fiddling functions. */
unsigned int gb_swap_nibbles(unsigned int n);
unsigned int gb_sla(unsigned int n);

/* Miscellaneous functions. */
void gb_daa();

/* Handle 0xCB instructions. */
void gb_cb();

/* Run the processor for the specified number of clock cycles. */
void gb_cpu_run(int cycles);

#endif
