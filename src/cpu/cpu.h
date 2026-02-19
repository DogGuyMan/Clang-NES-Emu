/**
 * @file cpu.h
 * @brief MOS 6502 CPU emulation interface.
 */
#ifndef NES_CPU_H
#define NES_CPU_H

#include "common/types.h"

struct Bus;

typedef union
{
	u8 raw;
	struct
	{
		u8 C : 1;
		u8 Z : 1;
		u8 I : 1;
		u8 D : 1;
		u8 B : 1;
		u8 dash : 1;
		u8 V : 1;
		u8 N : 1;
	} flags;
} Status;

typedef struct CPU
{
	u8 a, x, y, sp;
	Status status;
	u16 pc;
	u64 cycles;
	struct Bus *bus;

	bool nmi_pending;
	bool irq_pending;

	u8 opcode;
	u16 addr_abs;
	u16 addr_rel;
	u8 fetched;
	u8 remaining;
} CPU;

void cpu_init(CPU *cpu, struct Bus *bus);
void cpu_reset(CPU *cpu);
void cpu_step(CPU *cpu);
void cpu_nmi(CPU *cpu);
void cpu_irq(CPU *cpu);

#endif /* NES_CPU_H */
