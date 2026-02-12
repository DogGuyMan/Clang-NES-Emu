/**
 * @file ppu.c
 * @brief PPU emulation implementation.
 */
#include "ppu/ppu.h"

void ppu_init(PPU *ppu, PPUBus *bus) {
    (void)ppu;
    (void)bus;
    /* TODO: implement */
}

void ppu_reset(PPU *ppu) {
    (void)ppu;
    /* TODO: implement */
}

void ppu_step(PPU *ppu) {
    (void)ppu;
    /* TODO: implement */
}

u8 ppu_cpu_read(PPU *ppu, u16 addr) {
    (void)ppu;
    (void)addr;
    /* TODO: implement */
    return 0;
}

void ppu_cpu_write(PPU *ppu, u16 addr, u8 val) {
    (void)ppu;
    (void)addr;
    (void)val;
    /* TODO: implement */
}
