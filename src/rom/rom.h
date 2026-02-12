/**
 * @file rom.h
 * @brief iNES ROM parser interface.
 */
#ifndef NES_ROM_H
#define NES_ROM_H

#include "common/types.h"

typedef struct {
    u8  *prg_rom;
    u8  *chr_rom;
    u32  prg_rom_size;
    u32  chr_rom_size;
    u8   mapper_id;
    u8   mirroring;
    bool has_battery;
    bool has_trainer;
} ROM;

bool rom_load(ROM *rom, const char *filepath);
void rom_free(ROM *rom);

#endif /* NES_ROM_H */
