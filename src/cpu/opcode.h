/**
 * @file opcode.h
 * @brief MOS 6502 CPU emulation interface.
 */
#ifndef NES_OPCODE_H
#define NES_OPCODE_H

#include "common/types.h"
#include "cpu/cpu.h"

typedef struct OpcodeEntry
{
	const char *name;	      // 디버깅용
	u8 (*operate)(struct CPU *);  // returns 0 or 1 (extra cycle)
	u8 (*addrmode)(struct CPU *); // returns 0 or 1 (page cross)
	u8 cycles;		      // CycleCount
} OpcodeEntry;

OpcodeEntry opcodeTable[256];

#endif /* NES_OPCODE_H */
