/**
 * @file cpu.h
 * @brief MOS 6502 CPU emulation interface.
 */
#ifndef NES_CPU_H
#define NES_CPU_H

#include "common/types.h"

struct Bus;

typedef struct CPU {
    u8   a, x, y, sp, status;
    u16  pc;
    u64  cycles;
    struct Bus *bus;

    bool nmi_pending;
    bool irq_pending;

    u8   opcode;
    u16  addr_abs;
    u16  addr_rel;
    u8   fetched;
    u8   remaining;
} CPU;

void cpu_init(CPU *cpu, struct Bus *bus);
void cpu_reset(CPU *cpu);
void cpu_step(CPU *cpu);
void cpu_nmi(CPU *cpu);
void cpu_irq(CPU *cpu);

#endif /* NES_CPU_H */
