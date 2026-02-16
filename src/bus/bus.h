/**
 * @file bus.h
 * @brief CPU memory bus interface.
 */
#ifndef NES_BUS_H
#define NES_BUS_H

#include "common/types.h"
#include "mapper/mapper.h"

/* Forward declarations to avoid circular includes */
struct CPU;
struct PPU;
struct APU;

typedef struct Bus
{
	u8 ram[2048];
	struct CPU *cpu;
	struct PPU *ppu;
	struct APU *apu;
	Mapper *mapper;
	u8 controller[2];
	u8 controller_shift[2];
} Bus;

u8 bus_cpu_read(Bus *bus, u16 addr);
void bus_cpu_write(Bus *bus, u16 addr, u8 val);

#endif /* NES_BUS_H */
