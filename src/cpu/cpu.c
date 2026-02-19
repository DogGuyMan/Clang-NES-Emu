/**
 * @file cpu.c
 * @brief MOS 6502 CPU emulation implementation.
 */
#include "cpu/cpu.h"
#include "bus/bus.h"

#pragma region Bus Helper

static inline u8 read_bus_with_cpu(CPU *cpu, u16 addr)
{
	return bus_cpu_read(cpu->bus, addr);
}

static inline void write_bus_with_cpu(CPU *cpu, u16 addr, u8 val)
{
	bus_cpu_write(cpu->bus, addr, val);
}

#pragma endregion

#pragma region Stack Helper

#define STACK_START_ADDRESS 0x0100
#define STACK_SIZE 256

static inline void stack_push(CPU *cpu, u8 val)
{
	// 어차핀 sp는 u8이라 딱히 나머지 연산 안해도 됨
	write_bus_with_cpu(cpu, STACK_START_ADDRESS + (cpu->sp /*% STACK_SIZE*/), val);
	cpu->sp--;
}

static inline u8 stack_pop(CPU *cpu)
{
	cpu->sp++;
	// 어차핀 sp는 u8이라 딱히 나머지 연산 안해도 됨
	return read_bus_with_cpu(cpu, STACK_START_ADDRESS + (cpu->sp /*% STACK_SIZE*/));
}

#pragma endregion

#pragma region Status Helper

static inline void handle_status_nflag(CPU *cpu, const u8 val)
{
	// 0x80 == 1000 0000
	cpu->status.flags.N = (val & 0x80) ? 0x1 : 0x0;
}

static inline void handle_status_zflag(CPU *cpu, const u8 val)
{
	cpu->status.flags.Z = val ? 0x0 : 0x1;
}

#pragma endregion

#pragma region Fetch

static void cpu_fetch(CPU *cpu)
{
	u8 res = read_bus_with_cpu(cpu, cpu->addr_abs);
	cpu->fetched = res;
}

#pragma endregion

void cpu_init(CPU *cpu, Bus *bus)
{
	(void)cpu;
	(void)bus;
	/* TODO: implement */
}

void cpu_reset(CPU *cpu)
{
	(void)cpu;
	/* TODO: implement */
}

void cpu_step(CPU *cpu)
{
	(void)cpu;
	/* TODO: implement */
}

void cpu_nmi(CPU *cpu)
{
	(void)cpu;
	/* TODO: implement */
}

void cpu_irq(CPU *cpu)
{
	(void)cpu;
	/* TODO: implement */
}
