#ifndef GB_CPU_INSTRUCTION_CYCLES_H
#define GB_CPU_INSTRUCTION_CYCLES_H

const int GB_CPU_INSTRUCTION_CYCLES[256] = {
	4,  /* 0x00 */
	12, /* 0x01 */
	8,  /* 0x02 */
	8,  /* 0x03 */
	0,  /* 0x04 */
	0,  /* 0x05 */
	0,  /* 0x06 */
	4,  /* 0x07 */
	0,  /* 0x08 */
	0,  /* 0x09 */
	8,  /* 0x0A */
	8,  /* 0x0B */
	0,  /* 0x0C */
	0,  /* 0x0D */
	0,  /* 0x0E */
	4,  /* 0x0F */
	4,  /* 0x10 */
	0,  /* 0x11 */
	0,  /* 0x12 */
	8,  /* 0x13 */
	0,  /* 0x14 */
	0,  /* 0x15 */
	0,  /* 0x16 */
	4,  /* 0x17 */
	8,  /* 0x18 */
	0,  /* 0x19 */
	8,  /* 0x1A */
	8,  /* 0x1B */
	0,  /* 0x1C */
	0,  /* 0x1D */
	0,  /* 0x1E */
	4,  /* 0x1F */
	8,  /* 0x20 */
	0,  /* 0x21 */
	0,  /* 0x22 */
	8,  /* 0x23 */
	0,  /* 0x24 */
	0,  /* 0x25 */
	0,  /* 0x26 */
	4,  /* 0x27 */
	8,  /* 0x28 */
	0,  /* 0x29 */
	0,  /* 0x2A */
	8,  /* 0x2B */
	0,  /* 0x2C */
	0,  /* 0x2D */
	0,  /* 0x2E */
	4,  /* 0x2F */
	8,  /* 0x30 */
	0,  /* 0x31 */
	0,  /* 0x32 */
	8,  /* 0x33 */
	0,  /* 0x34 */
	0,  /* 0x35 */
	12, /* 0x36 */
	4,  /* 0x37 */
	8,  /* 0x38 */
	0,  /* 0x39 */
	0,  /* 0x3A */
	8,  /* 0x3B */
	0,  /* 0x3C */
	0,  /* 0x3D */
	8,  /* 0x3E */
	4,  /* 0x3F */
	4,  /* 0x40 */
	4,  /* 0x41 */
	4,  /* 0x42 */
	4,  /* 0x43 */
	4,  /* 0x44 */
	4,  /* 0x45 */
	8,  /* 0x46 */
	0,  /* 0x47 */
	4,  /* 0x48 */
	4,  /* 0x49 */
	4,  /* 0x4A */
	4,  /* 0x4B */
	4,  /* 0x4C */
	4,  /* 0x4D */
	8,  /* 0x4E */
	0,  /* 0x4F */
	4,  /* 0x50 */
	4,  /* 0x51 */
	4,  /* 0x52 */
	4,  /* 0x53 */
	4,  /* 0x54 */
	4,  /* 0x55 */
	8,  /* 0x56 */
	0,  /* 0x57 */
	4,  /* 0x58 */
	4,  /* 0x59 */
	4,  /* 0x5A */
	4,  /* 0x5B */
	4,  /* 0x5C */
	4,  /* 0x5D */
	8,  /* 0x5E */
	0,  /* 0x5F */
	4,  /* 0x60 */
	4,  /* 0x61 */
	4,  /* 0x62 */
	4,  /* 0x63 */
	4,  /* 0x64 */
	4,  /* 0x65 */
	8,  /* 0x66 */
	0,  /* 0x67 */
	4,  /* 0x68 */
	4,  /* 0x69 */
	4,  /* 0x6A */
	4,  /* 0x6B */
	4,  /* 0x6C */
	4,  /* 0x6D */
	8,  /* 0x6E */
	0,  /* 0x6F */
	8,  /* 0x70 */
	8,  /* 0x71 */
	8,  /* 0x72 */
	8,  /* 0x73 */
	8,  /* 0x74 */
	8,  /* 0x75 */
	4,  /* 0x76 */
	0,  /* 0x77 */
	4,  /* 0x78 */
	4,  /* 0x79 */
	4,  /* 0x7A */
	4,  /* 0x7B */
	4,  /* 0x7C */
	4,  /* 0x7D */
	8,  /* 0x7E */
	4,  /* 0x7F */
	0,  /* 0x80 */
	0,  /* 0x81 */
	0,  /* 0x82 */
	0,  /* 0x83 */
	0,  /* 0x84 */
	0,  /* 0x85 */
	0,  /* 0x86 */
	0,  /* 0x87 */
	0,  /* 0x88 */
	0,  /* 0x89 */
	0,  /* 0x8A */
	0,  /* 0x8B */
	0,  /* 0x8C */
	0,  /* 0x8D */
	0,  /* 0x8E */
	0,  /* 0x8F */
	0,  /* 0x90 */
	0,  /* 0x91 */
	0,  /* 0x92 */
	0,  /* 0x93 */
	0,  /* 0x94 */
	0,  /* 0x95 */
	0,  /* 0x96 */
	0,  /* 0x97 */
	0,  /* 0x98 */
	0,  /* 0x99 */
	0,  /* 0x9A */
	0,  /* 0x9B */
	0,  /* 0x9C */
	0,  /* 0x9D */
	0,  /* 0x9E */
	0,  /* 0x9F */
	0,  /* 0xA0 */
	0,  /* 0xA1 */
	0,  /* 0xA2 */
	0,  /* 0xA3 */
	0,  /* 0xA4 */
	0,  /* 0xA5 */
	0,  /* 0xA6 */
	0,  /* 0xA7 */
	0,  /* 0xA8 */
	0,  /* 0xA9 */
	0,  /* 0xAA */
	0,  /* 0xAB */
	0,  /* 0xAC */
	0,  /* 0xAD */
	0,  /* 0xAE */
	0,  /* 0xAF */
	0,  /* 0xB0 */
	0,  /* 0xB1 */
	0,  /* 0xB2 */
	0,  /* 0xB3 */
	0,  /* 0xB4 */
	0,  /* 0xB5 */
	0,  /* 0xB6 */
	0,  /* 0xB7 */
	0,  /* 0xB8 */
	0,  /* 0xB9 */
	0,  /* 0xBA */
	0,  /* 0xBB */
	0,  /* 0xBC */
	0,  /* 0xBD */
	0,  /* 0xBE */
	0,  /* 0xBF */
	8,  /* 0xC0 */
	0,  /* 0xC1 */
	12, /* 0xC2 */
	12, /* 0xC3 */
	12, /* 0xC4 */
	0,  /* 0xC5 */
	0,  /* 0xC6 */
	32, /* 0xC7 */
	8,  /* 0xC8 */
	8,  /* 0xC9 */
	0,  /* 0xCA */
	0,  /* 0xCB */
	12, /* 0xCC */
	12, /* 0xCD */
	0,  /* 0xCE */
	32, /* 0xCF */
	8,  /* 0xD0 */
	0,  /* 0xD1 */
	12, /* 0xD2 */
	0,  /* 0xD3 */
	12, /* 0xD4 */
	0,  /* 0xD5 */
	0,  /* 0xD6 */
	32, /* 0xD7 */
	8,  /* 0xD8 */
	8,  /* 0xD9 */
	12, /* 0xDA */
	0,  /* 0xDB */
	12, /* 0xDC */
	0,  /* 0xDD */
	0,  /* 0xDE */
	32, /* 0xDF */
	0,  /* 0xE0 */
	0,  /* 0xE1 */
	0,  /* 0xE2 */
	0,  /* 0xE3 */
	0,  /* 0xE4 */
	0,  /* 0xE5 */
	0,  /* 0xE6 */
	32, /* 0xE7 */
	0,  /* 0xE8 */
	4,  /* 0xE9 */
	0,  /* 0xEA */
	0,  /* 0xEB */
	0,  /* 0xEC */
	0,  /* 0xED */
	0,  /* 0xEE */
	32, /* 0xEF */
	0,  /* 0xF0 */
	0,  /* 0xF1 */
	0,  /* 0xF2 */
	4,  /* 0xF3 */
	0,  /* 0xF4 */
	0,  /* 0xF5 */
	0,  /* 0xF6 */
	32, /* 0xF7 */
	0,  /* 0xF8 */
	0,  /* 0xF9 */
	16, /* 0xFA */
	4,  /* 0xFB */
	0,  /* 0xFC */
	0,  /* 0xFD */
	0,  /* 0xFE */
	32, /* 0xFF */	
};

const int GB_CPU_INSTRUCTION_CYCLES_CB[256] = {
	8,  /* 0x00 */
	8,  /* 0x01 */
	8,  /* 0x02 */
	8,  /* 0x03 */
	8,  /* 0x04 */
	8,  /* 0x05 */
	16, /* 0x06 */
	8,  /* 0x07 */
	8,  /* 0x08 */
	8,  /* 0x09 */
	8,  /* 0x0A */
	8,  /* 0x0B */
	8,  /* 0x0C */
	8,  /* 0x0D */
	16, /* 0x0E */
	8,  /* 0x0F */
	8,  /* 0x10 */
	8,  /* 0x11 */
	8,  /* 0x12 */
	8,  /* 0x13 */
	8,  /* 0x14 */
	8,  /* 0x15 */
	16, /* 0x16 */
	8,  /* 0x17 */
	8,  /* 0x18 */
	8,  /* 0x19 */
	8,  /* 0x1A */
	8,  /* 0x1B */
	8,  /* 0x1C */
	8,  /* 0x1D */
	16, /* 0x1E */
	8,  /* 0x1F */
	0,  /* 0x20 */
	0,  /* 0x21 */
	0,  /* 0x22 */
	0,  /* 0x23 */
	0,  /* 0x24 */
	0,  /* 0x25 */
	0,  /* 0x26 */
	0,  /* 0x27 */
	0,  /* 0x28 */
	0,  /* 0x29 */
	0,  /* 0x2A */
	0,  /* 0x2B */
	0,  /* 0x2C */
	0,  /* 0x2D */
	0,  /* 0x2E */
	0,  /* 0x2F */
	0,  /* 0x30 */
	0,  /* 0x31 */
	0,  /* 0x32 */
	0,  /* 0x33 */
	0,  /* 0x34 */
	0,  /* 0x35 */
	0,  /* 0x36 */
	0,  /* 0x37 */
	0,  /* 0x38 */
	0,  /* 0x39 */
	0,  /* 0x3A */
	0,  /* 0x3B */
	0,  /* 0x3C */
	0,  /* 0x3D */
	0,  /* 0x3E */
	0,  /* 0x3F */
	0,  /* 0x40 */
	0,  /* 0x41 */
	0,  /* 0x42 */
	0,  /* 0x43 */
	0,  /* 0x44 */
	0,  /* 0x45 */
	0,  /* 0x46 */
	0,  /* 0x47 */
	0,  /* 0x48 */
	0,  /* 0x49 */
	0,  /* 0x4A */
	0,  /* 0x4B */
	0,  /* 0x4C */
	0,  /* 0x4D */
	0,  /* 0x4E */
	0,  /* 0x4F */
	0,  /* 0x50 */
	0,  /* 0x51 */
	0,  /* 0x52 */
	0,  /* 0x53 */
	0,  /* 0x54 */
	0,  /* 0x55 */
	0,  /* 0x56 */
	0,  /* 0x57 */
	0,  /* 0x58 */
	0,  /* 0x59 */
	0,  /* 0x5A */
	0,  /* 0x5B */
	0,  /* 0x5C */
	0,  /* 0x5D */
	0,  /* 0x5E */
	0,  /* 0x5F */
	0,  /* 0x60 */
	0,  /* 0x61 */
	0,  /* 0x62 */
	0,  /* 0x63 */
	0,  /* 0x64 */
	0,  /* 0x65 */
	0,  /* 0x66 */
	0,  /* 0x67 */
	0,  /* 0x68 */
	0,  /* 0x69 */
	0,  /* 0x6A */
	0,  /* 0x6B */
	0,  /* 0x6C */
	0,  /* 0x6D */
	0,  /* 0x6E */
	0,  /* 0x6F */
	0,  /* 0x70 */
	0,  /* 0x71 */
	0,  /* 0x72 */
	0,  /* 0x73 */
	0,  /* 0x74 */
	0,  /* 0x75 */
	0,  /* 0x76 */
	0,  /* 0x77 */
	0,  /* 0x78 */
	0,  /* 0x79 */
	0,  /* 0x7A */
	0,  /* 0x7B */
	0,  /* 0x7C */
	0,  /* 0x7D */
	0,  /* 0x7E */
	0,  /* 0x7F */
	0,  /* 0x80 */
	0,  /* 0x81 */
	0,  /* 0x82 */
	0,  /* 0x83 */
	0,  /* 0x84 */
	0,  /* 0x85 */
	0,  /* 0x86 */
	0,  /* 0x87 */
	0,  /* 0x88 */
	0,  /* 0x89 */
	0,  /* 0x8A */
	0,  /* 0x8B */
	0,  /* 0x8C */
	0,  /* 0x8D */
	0,  /* 0x8E */
	0,  /* 0x8F */
	0,  /* 0x90 */
	0,  /* 0x91 */
	0,  /* 0x92 */
	0,  /* 0x93 */
	0,  /* 0x94 */
	0,  /* 0x95 */
	0,  /* 0x96 */
	0,  /* 0x97 */
	0,  /* 0x98 */
	0,  /* 0x99 */
	0,  /* 0x9A */
	0,  /* 0x9B */
	0,  /* 0x9C */
	0,  /* 0x9D */
	0,  /* 0x9E */
	0,  /* 0x9F */
	0,  /* 0xA0 */
	0,  /* 0xA1 */
	0,  /* 0xA2 */
	0,  /* 0xA3 */
	0,  /* 0xA4 */
	0,  /* 0xA5 */
	0,  /* 0xA6 */
	0,  /* 0xA7 */
	0,  /* 0xA8 */
	0,  /* 0xA9 */
	0,  /* 0xAA */
	0,  /* 0xAB */
	0,  /* 0xAC */
	0,  /* 0xAD */
	0,  /* 0xAE */
	0,  /* 0xAF */
	0,  /* 0xB0 */
	0,  /* 0xB1 */
	0,  /* 0xB2 */
	0,  /* 0xB3 */
	0,  /* 0xB4 */
	0,  /* 0xB5 */
	0,  /* 0xB6 */
	0,  /* 0xB7 */
	0,  /* 0xB8 */
	0,  /* 0xB9 */
	0,  /* 0xBA */
	0,  /* 0xBB */
	0,  /* 0xBC */
	0,  /* 0xBD */
	0,  /* 0xBE */
	0,  /* 0xBF */
	0,  /* 0xC0 */
	0,  /* 0xC1 */
	0,  /* 0xC2 */
	0,  /* 0xC3 */
	0,  /* 0xC4 */
	0,  /* 0xC5 */
	0,  /* 0xC6 */
	0,  /* 0xC7 */
	0,  /* 0xC8 */
	0,  /* 0xC9 */
	0,  /* 0xCA */
	0,  /* 0xCB */
	0,  /* 0xCC */
	0,  /* 0xCD */
	0,  /* 0xCE */
	0,  /* 0xCF */
	0,  /* 0xD0 */
	0,  /* 0xD1 */
	0,  /* 0xD2 */
	0,  /* 0xD3 */
	0,  /* 0xD4 */
	0,  /* 0xD5 */
	0,  /* 0xD6 */
	0,  /* 0xD7 */
	0,  /* 0xD8 */
	0,  /* 0xD9 */
	0,  /* 0xDA */
	0,  /* 0xDB */
	0,  /* 0xDC */
	0,  /* 0xDD */
	0,  /* 0xDE */
	0,  /* 0xDF */
	0,  /* 0xE0 */
	0,  /* 0xE1 */
	0,  /* 0xE2 */
	0,  /* 0xE3 */
	0,  /* 0xE4 */
	0,  /* 0xE5 */
	0,  /* 0xE6 */
	0,  /* 0xE7 */
	0,  /* 0xE8 */
	0,  /* 0xE9 */
	0,  /* 0xEA */
	0,  /* 0xEB */
	0,  /* 0xEC */
	0,  /* 0xED */
	0,  /* 0xEE */
	0,  /* 0xEF */
	0,  /* 0xF0 */
	0,  /* 0xF1 */
	0,  /* 0xF2 */
	0,  /* 0xF3 */
	0,  /* 0xF4 */
	0,  /* 0xF5 */
	0,  /* 0xF6 */
	0,  /* 0xF7 */
	0,  /* 0xF8 */
	0,  /* 0xF9 */
	0,  /* 0xFA */
	0,  /* 0xFB */
	0,  /* 0xFC */
	0,  /* 0xFD */
	0,  /* 0xFE */
	0,  /* 0xFF */	
};

#endif
