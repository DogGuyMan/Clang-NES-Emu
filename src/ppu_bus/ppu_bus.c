/**
 * @file ppu_bus.c
 * @brief PPU memory bus implementation.
 */
#include "ppu_bus/ppu_bus.h"

u8 ppu_bus_read(PPUBus *bus, u16 addr) {
    (void)bus;
    (void)addr;
    /* TODO: implement PPU address decoding */
    return 0;
}

void ppu_bus_write(PPUBus *bus, u16 addr, u8 val) {
    (void)bus;
    (void)addr;
    (void)val;
    /* TODO: implement PPU address decoding */
}
