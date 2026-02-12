/**
 * @file mapper.h
 * @brief Mapper interface (polymorphic via function pointers).
 */
#ifndef NES_MAPPER_H
#define NES_MAPPER_H

#include "common/types.h"
#include "rom/rom.h"

typedef struct Mapper {
    u8   id;
    void *state;

    u8   (*cpu_read)(struct Mapper *m, u16 addr);
    void (*cpu_write)(struct Mapper *m, u16 addr, u8 val);
    u8   (*ppu_read)(struct Mapper *m, u16 addr);
    void (*ppu_write)(struct Mapper *m, u16 addr, u8 val);

    u8   (*get_mirroring)(struct Mapper *m);
    bool (*irq_pending)(struct Mapper *m);
    void (*scanline_counter)(struct Mapper *m);

    void (*free)(struct Mapper *m);
} Mapper;

Mapper *mapper_create(ROM *rom);

#endif /* NES_MAPPER_H */
