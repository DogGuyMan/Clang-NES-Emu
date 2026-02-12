/**
 * @file ppu.h
 * @brief PPU (Picture Processing Unit) emulation interface.
 */
#ifndef NES_PPU_H
#define NES_PPU_H

#include "common/types.h"
#include "ppu_bus/ppu_bus.h"

typedef struct PPU
{
	PPUBus *bus;

	u8 ctrl;
	u8 mask;
	u8 status;
	u8 oam_addr;

	u16 v;
	u16 t;
	u8 x;
	u8 w;

	u8 data_buffer;
	u8 oam[256];

	s16 scanline;
	u16 cycle;

	u16 bg_shifter_pattern_lo;
	u16 bg_shifter_pattern_hi;
	u16 bg_shifter_attrib_lo;
	u16 bg_shifter_attrib_hi;
	u8 bg_next_tile_id;
	u8 bg_next_tile_attrib;
	u8 bg_next_tile_lsb;
	u8 bg_next_tile_msb;

	u8 sprite_scanline[32];
	u8 sprite_count;
	u8 sprite_shifter_lo[8];
	u8 sprite_shifter_hi[8];
	bool sprite_zero_hit_possible;
	bool sprite_zero_being_rendered;

	u32 framebuffer[256 * 240];
	bool frame_complete;
	bool nmi_occurred;

	u64 frame_count;
	bool odd_frame;
} PPU;

void ppu_init(PPU *ppu, PPUBus *bus);
void ppu_reset(PPU *ppu);
void ppu_step(PPU *ppu);
u8 ppu_cpu_read(PPU *ppu, u16 addr);
void ppu_cpu_write(PPU *ppu, u16 addr, u8 val);

#endif /* NES_PPU_H */
