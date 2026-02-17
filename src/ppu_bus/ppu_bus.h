/**
 * @file ppu_bus.h
 * @brief PPU memory bus interface.
 */
#ifndef NES_PPU_BUS_H
#define NES_PPU_BUS_H

#include "common/types.h"
#include "mapper/mapper.h"

#define PPU_ADDRESS_WARPPING_MASK 0x3FFF
#define PPU_PATTERN_TABLE_ADDRESSS_BARRIER 0x2000
#define PPU_NAME_TABLE_ADDRESSS_BARRIER 0x3000
#define PPU_PALETTE_RAM_ADDRESS 0x3F00

typedef struct PPUBus
{
	u8 vram[2048]; // 딱 0x0000-0x0800 만큼의 분량이다.
	u8 palette[32];
	Mapper *mapper;
} PPUBus;

u8 ppu_bus_read(PPUBus *bus, u16 addr);
void ppu_bus_write(PPUBus *bus, u16 addr, u8 val);

#endif /* NES_PPU_BUS_H */
