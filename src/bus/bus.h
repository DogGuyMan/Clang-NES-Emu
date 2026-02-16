/**
 * @file bus.h
 * @brief CPU memory bus interface.
 */
#ifndef NES_BUS_H
#define NES_BUS_H

#include "common/types.h"
#include "mapper/mapper.h"

// 0000 0111 1111 1111
// 0000 1XXX XXXX XXXX
#define CPU_INTERNAL_RAM_MIRROR_MASK (0x0800 - 1)
// 0000 0000 0000 0111
#define CPU_PPU_REGISTER_MIRROR_MASK (0x0008 - 1)
#define CPU_RAM_ADDRESS_BARRIER 0x2000
#define CPU_PPU_REGISTER_ADDRESS_BARRIER 0x4000
#define CPU_OAM_DMA_ADDRESS 0x4014
#define CPU_CONTROLLERS_FIRST_ADDRESS 0x4016
#define CPU_CONTROLLERS_SECOND_ADDRESS 0x4017
#define CPU_MAPPER_ADDRESS 0x4020

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
