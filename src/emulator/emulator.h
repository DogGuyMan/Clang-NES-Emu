/**
 * @file emulator.h
 * @brief Emulator main loop and timing synchronization.
 */
#ifndef NES_EMULATOR_H
#define NES_EMULATOR_H

#include "common/types.h"
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "apu/apu.h"
#include "bus/bus.h"
#include "ppu_bus/ppu_bus.h"
#include "mapper/mapper.h"
#include "input/input.h"
#include "rom/rom.h"

typedef struct {
    CPU        cpu;
    PPU        ppu;
    APU        apu;
    Bus        cpu_bus;
    PPUBus     ppu_bus;
    Mapper    *mapper;
    Controller ctrl[2];
    ROM        rom;
    bool       running;
} Emulator;

bool emulator_init(Emulator *emu, const char *rom_path);
void emulator_run(Emulator *emu);
void emulator_step_frame(Emulator *emu);
void emulator_destroy(Emulator *emu);

#endif /* NES_EMULATOR_H */
