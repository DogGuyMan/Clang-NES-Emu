/**
 * @file ppu_bus.h
 * @brief PPU memory bus interface.
 */
#ifndef NES_PPU_BUS_H
#define NES_PPU_BUS_H

#include "common/types.h"
#include "mapper/mapper.h"

typedef struct PPUBus
{
	u8 vram[2048];
	u8 palette[32];
	Mapper *mapper;
} PPUBus;

u8 ppu_bus_read(PPUBus *bus, u16 addr);
void ppu_bus_write(PPUBus *bus, u16 addr, u8 val);

#endif /* NES_PPU_BUS_H */
