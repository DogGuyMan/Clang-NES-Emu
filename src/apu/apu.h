/**
 * @file apu.h
 * @brief APU (Audio Processing Unit) emulation interface.
 */
#ifndef NES_APU_H
#define NES_APU_H

#include "common/types.h"

struct Bus;

typedef struct APU {
    u8   frame_counter_mode;
    bool irq_inhibit;
    bool frame_irq;
    u64  cycle;

    struct Bus *bus;
} APU;

void apu_init(APU *apu, struct Bus *bus);
void apu_step(APU *apu);
u8   apu_read(APU *apu, u16 addr);
void apu_write(APU *apu, u16 addr, u8 val);

#endif /* NES_APU_H */
