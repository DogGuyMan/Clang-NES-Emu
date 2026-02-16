/**
 * @file mapper.h
 * @brief Mapper interface (polymorphic via function pointers).
 */
#ifndef NES_MAPPER_H
#define NES_MAPPER_H

#include "common/types.h"
#include "rom/rom.h"

// 1000 0000 0000 0000
#define PRG_ADDRESS_OFFSET 0x8000

// 0011 1111 1111 1111
// 01XX XXXX XXXX XXXX -> 00XX XXXX XXXX XXXX
#define PRG_16K_MIRROR_MASK 0x3FFF

// 0111 1111 1111 1111
// 01XX XXXX XXXX XXXX -> 01XX XXXX XXXX XXXX
#define PRG_32K_MIRROR_MASK 0x7FFF

#define PPU_ADDRESS_EXIT 0x2000

#define GET_MAPPER_STATE(TYPE, MAPPER_PTR) ((TYPE *)(MAPPER_PTR)->state)

typedef struct Mapper
{
	u8 id;
	void *state;

	u8 (*const cpu_read)(struct Mapper *m, u16 addr);
	void (*const cpu_write)(struct Mapper *m, u16 addr, u8 val);
	u8 (*const ppu_read)(struct Mapper *m, u16 addr);
	void (*const ppu_write)(struct Mapper *m, u16 addr, u8 val);

	u8 (*const get_mirroring)(struct Mapper *m);
	bool (*const irq_pending)(struct Mapper *m);
	void (*const scanline_counter)(struct Mapper *m);

	void (*const free)(struct Mapper *m);
} Mapper;

Mapper *mapper_create(ROM *rom);
void mapper_free(Mapper *m);

#endif /* NES_MAPPER_H */
