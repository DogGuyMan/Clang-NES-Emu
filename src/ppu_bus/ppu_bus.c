/**
 * @file ppu_bus.c
 * @brief PPU memory bus implementation.
 */
#include "ppu_bus/ppu_bus.h"

static inline void address_warpping(u16 *addr_out)
{
	(*addr_out) &= PPU_ADDRESS_WARPPING_MASK;
}

#pragma region Patterntable

static inline bool ppu_bus_pattern_table_predicate(u16 addr)
{
	return addr < PPU_PATTERN_TABLE_ADDRESSS_BARRIER;
}

static inline u8 ppu_bus_pattern_table_read(PPUBus *bus, u16 addr)
{
	return bus->mapper->ppu_read(bus->mapper, addr);
}

static inline void ppu_bus_pattern_table_write(PPUBus *bus, u16 addr, u8 val)
{
	bus->mapper->ppu_write(bus->mapper, addr, val);
}

#pragma endregion

#pragma region Nametable

static inline bool ppu_bus_nametable_predicate(u16 addr)
{
	return PPU_PATTERN_TABLE_ADDRESSS_BARRIER <= addr && addr < PPU_PALETTE_RAM_ADDRESS;
}

static inline void nametable_address_warpping(u16 *addr_out)
{
	const u16 addr_readonly = *addr_out;
	if (PPU_NAME_TABLE_ADDRESSS_BARRIER <= addr_readonly)
		(*addr_out) -= 0x1000;
}

static inline u8 nametable_virtucal_nt(u16 addr)
{
	u8 res = 0xFF;
	if ((0x2000 <= addr && addr < 0x2400) || (0x2800 <= addr && addr < 0x2C00))
		res = 0;
	if ((0x2400 <= addr && addr < 0x2800) || (0x2C00 <= addr && addr < 0x3000))
		res = 1;
	return res;
}

static inline u8 nametable_horizontal_nt(u16 addr)
{
	u8 res = 0xFF;
	if ((0x2000 <= addr && addr < 0x2400) || (0x2400 <= addr && addr < 0x2800))
		res = 0;
	if ((0x2800 <= addr && addr < 0x2C00) || (0x2C00 <= addr && addr < 0x3000))
		res = 1;
	return res;
}

static inline u8 ppu_bus_nametable_read(PPUBus *bus, u16 addr)
{
	nametable_address_warpping(&addr);
	u8 mirroring = bus->mapper->get_mirroring(bus->mapper);
	u8 nt = (mirroring == NAMETABLE_ARRANGEMENT_VERTICAL_FLAG) ? nametable_virtucal_nt(addr) : nametable_horizontal_nt(addr);
	return bus->vram[(nt * 0x400) + (addr & 0x3FF)];
}

static inline void ppu_bus_nametable_write(PPUBus *bus, u16 addr, u8 val)
{
	nametable_address_warpping(&addr);
	u8 mirroring = bus->mapper->get_mirroring(bus->mapper);
	u8 nt = (mirroring == NAMETABLE_ARRANGEMENT_VERTICAL_FLAG) ? nametable_virtucal_nt(addr) : nametable_horizontal_nt(addr);
	bus->vram[(nt * 0x400) + (addr & 0x3FF)] = val;
}

#pragma endregion

#pragma region Palette

// FF를 32(0x001F)개로 팔레트로 나눈다면
// 8개는 미러링 되야한다.
static inline bool ppu_bus_palette_ram_predicate(u16 addr)
{
	return PPU_PALETTE_RAM_ADDRESS <= addr && addr < PPU_PALETTE_RAM_ADDRESS + 0x0100;
}

static inline u8 ppu_bus_palette_ram_read(PPUBus *bus, u16 addr)
{
	u8 palette_idx = addr & 0x001F;
	if (palette_idx >= 16 && palette_idx % 4 == 0)
		return bus->palette[palette_idx & 0x000F];
	return bus->palette[palette_idx];
}
static inline void ppu_bus_palette_ram_write(PPUBus *bus, u16 addr, u8 val)
{
	u8 palette_idx = addr & 0x001F;
	if (palette_idx >= 16 && palette_idx % 4 == 0)
		bus->palette[palette_idx & 0x000F] = val;
	else
		bus->palette[palette_idx] = val;
}

#pragma endregion

u8 ppu_bus_read(PPUBus *bus, u16 addr)
{
	address_warpping(&addr);
	if (ppu_bus_pattern_table_predicate(addr))
		return ppu_bus_pattern_table_read(bus, addr);
	if (ppu_bus_nametable_predicate(addr))
		return ppu_bus_nametable_read(bus, addr);
	if (ppu_bus_palette_ram_predicate(addr))
		return ppu_bus_palette_ram_read(bus, addr);
	// ! TODO
	return 0;
}

void ppu_bus_write(PPUBus *bus, u16 addr, u8 val)
{
	address_warpping(&addr);
	if (ppu_bus_pattern_table_predicate(addr))
		ppu_bus_pattern_table_write(bus, addr, val);
	else if (ppu_bus_nametable_predicate(addr))
		ppu_bus_nametable_write(bus, addr, val);
	else if (ppu_bus_palette_ram_predicate(addr))
		ppu_bus_palette_ram_write(bus, addr, val);
}
