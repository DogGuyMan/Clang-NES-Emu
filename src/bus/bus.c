/**
 * @file bus.c
 * @brief CPU memory bus implementation.
 */
#include "bus/bus.h"
#include "apu/apu.h"
#include "common/log.h"
#include "input/input.h"
#include "ppu/ppu.h"

#pragma region Internal Ram

static inline bool bus_cpu_internal_ram_predicate(u16 addr)
{
	return addr < CPU_RAM_ADDRESS_BARRIER;
}

static inline u8 bus_cpu_internal_ram_read(Bus *bus, u16 addr)
{
	u16 offseted_addr = addr & CPU_INTERNAL_RAM_MIRROR_MASK;
	return bus->ram[offseted_addr];
}

static inline void bus_cpu_internal_ram_write(Bus *bus, u16 addr, u8 val)
{
	u16 offseted_addr = addr & CPU_INTERNAL_RAM_MIRROR_MASK;
	bus->ram[offseted_addr] = val;
}

#pragma endregion

#pragma region PPU Register

static inline bool bus_cpu_ppu_registers_predicate(u16 addr)
{
	return CPU_RAM_ADDRESS_BARRIER <= addr && addr < CPU_PPU_REGISTER_ADDRESS_BARRIER;
}

static inline u8 bus_cpu_ppu_registers_read(Bus *bus, u16 addr)
{
	u16 reg = ((addr - CPU_RAM_ADDRESS_BARRIER) & CPU_PPU_REGISTER_MIRROR_MASK);
	return ppu_cpu_read(bus->ppu, reg);
}

static inline void bus_cpu_ppu_registers_write(Bus *bus, u16 addr, u8 val)
{
	u16 reg = ((addr - CPU_RAM_ADDRESS_BARRIER) & CPU_PPU_REGISTER_MIRROR_MASK);
	ppu_cpu_write(bus->ppu, reg, val);
}

#pragma endregion

#pragma region OAM DMA

static inline bool bus_cpu_oam_dma_predicate(u16 addr)
{
	return addr == CPU_OAM_DMA_ADDRESS;
}

static inline void bus_cpu_oam_dma_write(Bus *bus, u16 addr, u8 val)
{
	LOG_WARN("TODO OAM DMA");
}

#pragma endregion

#pragma region APU Register

static inline bool bus_cpu_apu_register_read_predicate(u16 addr)
{
	return (CPU_PPU_REGISTER_ADDRESS_BARRIER <= addr && addr <= CPU_PPU_REGISTER_ADDRESS_BARRIER + 0x15) && (addr != CPU_OAM_DMA_ADDRESS);
}

static inline bool bus_cpu_apu_register_write_predicate(u16 addr)
{
	// ! 0x4017 는 read에서는 controller 2
	// ! 그런데 write에서는 apu를 가르키는 방식이란다..
	return bus_cpu_apu_register_read_predicate(addr) || addr == 0x4017;
}

static inline u8 bus_cpu_apu_registers_read(Bus *bus, u16 addr)
{
	return apu_read(bus->apu, addr);
}

static inline void bus_cpu_apu_registers_write(Bus *bus, u16 addr, u8 val)
{
	apu_write(bus->apu, addr, val);
}

#pragma endregion

#pragma region Controllers

static inline bool bus_cpu_controllers_read_predicate(u16 addr)
{
	return CPU_CONTROLLERS_FIRST_ADDRESS == addr ||
	       CPU_CONTROLLERS_SECOND_ADDRESS == addr;
}

static inline bool bus_cpu_controllers_write_predicate(u16 addr)
{
	return CPU_CONTROLLERS_FIRST_ADDRESS == addr;
}

static inline u8 bus_cpu_controllers_read(Bus *bus, u16 addr)
{
	u8 res = bus->controller_shift[addr - CPU_CONTROLLERS_FIRST_ADDRESS] & 0x1;
	bus->controller_shift[addr - CPU_CONTROLLERS_FIRST_ADDRESS] >>= 1;
	return res;
}

static inline void bus_cpu_controllers_write(Bus *bus, u16 addr, u8 val)
{
	if (val & 0x1)
	{
		bus->controller_shift[0] = bus->controller[0];
		bus->controller_shift[1] = bus->controller[1];
	}
}

#pragma endregion

#pragma region Mapper

static inline bool bus_cpu_mapper_predicate(u16 addr)
{
	return CPU_MAPPER_ADDRESS <= addr;
}

static inline u8 bus_cpu_mapper_read(Bus *bus, u16 addr)
{
	return bus->mapper->cpu_read(bus->mapper, addr);
}

static inline void bus_cpu_mapper_write(Bus *bus, u16 addr, u8 val)
{
	bus->mapper->cpu_write(bus->mapper, addr, val);
}

#pragma endregion

u8 bus_cpu_read(Bus *bus, u16 addr)
{
	if (bus_cpu_internal_ram_predicate(addr))
		return bus_cpu_internal_ram_read(bus, addr);
	if (bus_cpu_ppu_registers_predicate(addr))
		return bus_cpu_ppu_registers_read(bus, addr);
	if (bus_cpu_apu_register_read_predicate(addr))
		return bus_cpu_apu_registers_read(bus, addr);
	if (0x4018 <= addr && addr <= 0x401F) // Open Bus 처리
		return 0;
	if (bus_cpu_controllers_read_predicate(addr))
		return bus_cpu_controllers_read(bus, addr);
	if (bus_cpu_mapper_predicate(addr))
		return bus_cpu_mapper_read(bus, addr);
	return 0;
}

void bus_cpu_write(Bus *bus, u16 addr, u8 val)
{
	if (bus_cpu_internal_ram_predicate(addr))
		bus_cpu_internal_ram_write(bus, addr, val);
	else if (bus_cpu_ppu_registers_predicate(addr))
		bus_cpu_ppu_registers_write(bus, addr, val);
	else if (bus_cpu_oam_dma_predicate(addr))
		bus_cpu_oam_dma_write(bus, addr, val);
	else if (bus_cpu_apu_register_write_predicate(addr))
		bus_cpu_apu_registers_write(bus, addr, val);
	else if (0x4018 <= addr && addr <= 0x401F) // Open Bus 처리
		bus_cpu_controllers_write(bus, addr, val);
	else if (bus_cpu_mapper_predicate(addr))
		bus_cpu_mapper_write(bus, addr, val);
}
