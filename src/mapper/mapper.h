/**
 * @file mapper.h
 * @brief Mapper interface (polymorphic via function pointers).
 */
#ifndef NES_MAPPER_H
#define NES_MAPPER_H

#include "common/types.h"
#include "rom/rom.h"

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

#endif /* NES_MAPPER_H */
