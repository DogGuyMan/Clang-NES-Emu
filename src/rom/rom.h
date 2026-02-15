/**
 * @file rom.h
 * @brief iNES ROM parser interface.
 */
#ifndef NES_ROM_H
#define NES_ROM_H

#include "common/types.h"

// 수직 배치 & 수평 미러링
#define NAMETABLE_ARRANGEMENT_HORIZONTAL_FLAG 0

// 수평 배치 & 수직 미러링
#define NAMETABLE_ARRANGEMENT_VERTICAL_FLAG 1

typedef union
{
	u8 raw;
	struct
	{
		u8 nametable_arrangement : 1;
		u8 battery_backed_prg : 1;
		u8 has_trainer : 1;
		u8 alternative_nametable_layout : 1;
		u8 mapper_lower_nibble : 4;
	} flags;
} Flags6;

typedef union
{
	u8 raw;

	struct
	{
		u8 vs_unisystem : 1;
		u8 play_choice : 1;
		u8 nes_2_id : 2;
		u8 mapper_upper_nibble : 4;
	} flags;
} Flags7;

typedef u8 Flags8;
typedef u8 Flags9;
typedef u8 FlagsA;
typedef u8 FlagsB;
typedef u8 FlagsC;
typedef u8 FlagsD;
typedef u8 FlagsE;
typedef u8 FlagsF;

typedef struct ROMHeader
{
	u8 magic_numbers[4];	   // 0-3
	u8 prg_rom_size;	   // 4
	u8 chr_rom_size;	   // 5
	Flags6 mapper_lower_flags; // 6 매퍼, 미러링, 배터리, 트레이너
	Flags7 mapper_upper_flags; // 7 매퍼, VS/Playchoice, NES 2.0
	Flags8 prg_ram_size;	   // 8
	Flags9 tv_system_1;	   // 9
	FlagsA tv_system_2;	   // 10
	FlagsB unused_pad_1;	   // 11
	FlagsC unused_pad_2;
	FlagsD unused_pad_3;
	FlagsE unused_pad_4;
	FlagsF unused_pad_5;
} ROMHeader;

#define ROM_HEADER_SIZE 16
#define ROM_TRAINER_SIZE 512
#define ROM_PRG_BANK_SIZE (1 << 14)
#define ROM_CHR_BANK_SIZE (1 << 13)
typedef struct ROM
{
	struct ROMHeader header;
	u8 mapper_id;
	u8 *trainer_rom_ptr;
	u8 *prg_rom_ptr;
	u8 *chr_rom_ptr;
	void (*const rom_free)(struct ROM *this);
} ROM;

bool rom_load(struct ROM *rom, const char *filepath);
void rom_free(struct ROM *rom);
#endif /* NES_ROM_H */
