#ifndef GB_MEM_H
#define GB_MEM_H

unsigned int gb_mem_get(int offset);
int gb_mem_get_signed(int offset);
void gb_mem_set(int offset, unsigned int n);

unsigned int gb_mem_get_16(int offset);
void gb_mem_set_16(int offset, unsigned int n);

#endif
