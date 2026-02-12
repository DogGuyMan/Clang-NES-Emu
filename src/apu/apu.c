/**
 * @file apu.c
 * @brief APU emulation implementation.
 */
#include "apu/apu.h"

void apu_init(APU *apu, struct Bus *bus) {
    (void)apu;
    (void)bus;
    /* TODO: implement */
}

void apu_step(APU *apu) {
    (void)apu;
    /* TODO: implement */
}

u8 apu_read(APU *apu, u16 addr) {
    (void)apu;
    (void)addr;
    /* TODO: implement */
    return 0;
}

void apu_write(APU *apu, u16 addr, u8 val) {
    (void)apu;
    (void)addr;
    (void)val;
    /* TODO: implement */
}
