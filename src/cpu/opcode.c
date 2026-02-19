/**
 * @file opcode.c
 * @brief MOS 6502 CPU emulation implementation.
 */

#include "cpu/opcode.h"
#include "cpu/cpu.h"
#include <stdlib.h>

#pragma region Addressing

// SIMPLE
u8 IMP(struct CPU *cpu)
{
	abort();
}
u8 ACC(struct CPU *cpu)
{
	abort();
}
u8 IMM(struct CPU *cpu)
{
	abort();
}

// ZERO PAGE
u8 ZP0(struct CPU *cpu)
{
	//(ADDR) % 0x0100
	abort();
}
u8 ZPX(struct CPU *cpu)
{
	//(ADDR + X) % 0x0100
	abort();
}
u8 ZPY(struct CPU *cpu)
{
	//(ADDR + Y) % 0x0100
	abort();
}

// ABSOLUTE
// Page Crossing 현상 대응해야함
// 캐리가 발생하면(페이지를 넘었으면)
// 이때는 Cycle이 하나 더 생길 수 있다.

u8 ABS(struct CPU *cpu)
{
	abort();
}
u8 ABX(struct CPU *cpu)
{
	abort();
}
u8 ABY(struct CPU *cpu)
{
	abort();
}

// INDIRECT

// 주의할 것은 JMP 버그에 대해 대응해야 하고 마찬가지로
// Page Crossing 대응해야함
u8 IND(struct CPU *cpu)
{
	abort();
}
u8 IZX(struct CPU *cpu)
{
	abort();
}
u8 IZY(struct CPU *cpu)
{
	abort();
}

// RELATIVE
u8 REL(struct CPU *cpu)
{
	abort();
}

#pragma endregion

#pragma region Operate

// 1.	LoadStore
u8 LDA(struct CPU *cpu)
{
	abort();
}
u8 LDX(struct CPU *cpu)
{
	abort();
}
u8 LDY(struct CPU *cpu)
{
	abort();
}
u8 STA(struct CPU *cpu)
{
	abort();
}
u8 STX(struct CPU *cpu)
{
	abort();
}
u8 STY(struct CPU *cpu)
{
	abort();
}
// 2.	Transfer
u8 TAX(struct CPU *cpu)
{
	abort();
}
u8 TAY(struct CPU *cpu)
{
	abort();
}
u8 TSX(struct CPU *cpu)
{
	abort();
}
u8 TXA(struct CPU *cpu)
{
	abort();
}
u8 TXS(struct CPU *cpu)
{
	abort();
}
u8 TYA(struct CPU *cpu)
{
	abort();
}
// 3.	Stack
u8 PHA(struct CPU *cpu)
{
	abort();
}
u8 PHP(struct CPU *cpu)
{
	abort();
}
u8 PLA(struct CPU *cpu)
{
	abort();
}
u8 PLP(struct CPU *cpu)
{
	abort();
}
// 4.	산술
// SBC (V 플래그 처리가 핵심)
u8 ADC(struct CPU *cpu)
{
	abort();
}
u8 SBC(struct CPU *cpu)
{
	abort();
}
// 5.	논리
u8 AND(struct CPU *cpu)
{
	abort();
}
u8 ORA(struct CPU *cpu)
{
	abort();
}
u8 EOR(struct CPU *cpu)
{
	abort();
}
u8 BIT(struct CPU *cpu)
{
	abort();
}
// 6.	시프트회전
// ROR (ACC 모드 vs 메모리 모드)
u8 ASL(struct CPU *cpu)
{
	abort();
}
u8 LSR(struct CPU *cpu)
{
	abort();
}
u8 ROL(struct CPU *cpu)
{
	abort();
}
u8 ROR(struct CPU *cpu)
{
	abort();
}
// 7.	증감
u8 INC(struct CPU *cpu)
{
	abort();
}
u8 INX(struct CPU *cpu)
{
	abort();
}
u8 INY(struct CPU *cpu)
{
	abort();
}
u8 DEC(struct CPU *cpu)
{
	abort();
}
u8 DEX(struct CPU *cpu)
{
	abort();
}
u8 DEY(struct CPU *cpu)
{
	abort();
}
// 8.	비교
u8 CMP(struct CPU *cpu)
{
	abort();
}
u8 CPX(struct CPU *cpu)
{
	abort();
}
u8 CPY(struct CPU *cpu)
{
	abort();
}
// 9.	분기
// BVS (페이지 크로싱 +1 사이클)
u8 BCC(struct CPU *cpu)
{
	abort();
}
u8 BCS(struct CPU *cpu)
{
	abort();
}
u8 BEQ(struct CPU *cpu)
{
	abort();
}
u8 BMI(struct CPU *cpu)
{
	abort();
}
u8 BNE(struct CPU *cpu)
{
	abort();
}
u8 BPL(struct CPU *cpu)
{
	abort();
}
u8 BVC(struct CPU *cpu)
{
	abort();
}
u8 BVS(struct CPU *cpu)
{
	abort();
}
// 10.	점프서브루틴
u8 JMP(struct CPU *cpu)
{
	abort();
}
u8 JSR(struct CPU *cpu)
{
	abort();
}
u8 RTS(struct CPU *cpu)
{
	abort();
}
u8 RTI(struct CPU *cpu)
{
	abort();
}
// 11.	플래그
u8 CLC(struct CPU *cpu)
{
	abort();
}
u8 CLD(struct CPU *cpu)
{
	abort();
}
u8 CLI(struct CPU *cpu)
{
	abort();
}
u8 CLV(struct CPU *cpu)
{
	abort();
}
u8 SEC(struct CPU *cpu)
{
	abort();
}
u8 SED(struct CPU *cpu)
{
	abort();
}
u8 SEI(struct CPU *cpu)
{
	abort();
}
// 12.	시스템
u8 BRK(struct CPU *cpu)
{
	abort();
}
u8 NOP(struct CPU *cpu)
{
	abort();
}
#pragma endregion

// ADDR 모드 * OPERATE에 따라 Inst를 각각 만드는것은 너무.. 노다가임
OpcodeEntry opcodeTable[256] = {
    /* ***************************************** */
    /*			Access			 */
    /* ***************************************** */

    /* LDA */
    [0xA9] = {"LDA", LDA, IMM, 2},
    [0xA5] = {"LDA", LDA, ZP0, 3},
    [0xB5] = {"LDA", LDA, ZPX, 4},
    [0xAD] = {"LDA", LDA, ABS, 4},
    [0xBD] = {"LDA", LDA, ABX, 4}, // Page Crossing + 1
    [0xB9] = {"LDA", LDA, ABY, 4}, // Page Crossing + 1
    [0xA1] = {"LDA", LDA, IZX, 6},
    [0xB1] = {"LDA", LDA, IZY, 5}, // Page Crossing + 1

    /* STA */
    [0x85] = {"STA", STA, ZP0, 3},
    [0x95] = {"STA", STA, ZPX, 4},
    [0x8D] = {"STA", STA, ABS, 4},
    [0x9D] = {"STA", STA, ABX, 5},
    [0x99] = {"STA", STA, ABY, 5},
    [0x81] = {"STA", STA, IZX, 6},
    [0x91] = {"STA", STA, IZY, 6},

    /* LDX */

    [0xA2] = {"LDX", LDX, IMM, 2},
    [0xA6] = {"LDX", LDX, ZP0, 3},
    [0xB6] = {"LDX", LDX, ZPY, 4},
    [0xAE] = {"LDX", LDX, ABS, 4},
    [0xBE] = {"LDX", LDX, ABY, 4}, // Page Crossing + 1

    /* STX */

    [0x86] = {"STX", STX, ZP0, 3},
    [0x96] = {"STX", STX, ZPY, 4},
    [0x8E] = {"STX", STX, ABS, 4},

    /* LDY */
    // Z - 제로	result == 0
    // N - 네거티브	result 비트 7
    [0xA0] = {"LDY", LDY, IMM, 2},
    [0xA4] = {"LDY", LDY, ZP0, 3},
    [0xB4] = {"LDY", LDY, ZPX, 4},
    [0xAC] = {"LDY", LDY, ABS, 4},
    [0xBC] = {"LDY", LDY, ABX, 4}, // Page Crossing + 1

    /* STY */
    [0x84] = {"STY", STY, ZP0, 3},
    [0x94] = {"STY", STY, ZPX, 4},
    [0x8C] = {"STY", STY, ABS, 4},

    /* ***************************************** */
    /*			Transfer		 */
    /* ***************************************** */

    /* TAX */
    [0xAA] = {"TAX", TAX, IMP, 2},

    /* TXA */
    [0x8A] = {"TXA", TXA, IMP, 2},

    /* TAY */
    [0xA8] = {"TAY", TAY, IMP, 2},

    /* TYA */
    [0x98] = {"TYA", TYA, IMP, 2},

    /* ***************************************** */
    /*			Arithmetic		 */
    /* ***************************************** */

    /* ADC */
    [0x69] = {"ADC", ADC, IMM, 2},
    [0x65] = {"ADC", ADC, ZP0, 3},
    [0x75] = {"ADC", ADC, ZPX, 4},
    [0x6D] = {"ADC", ADC, ABS, 4},
    [0x7D] = {"ADC", ADC, ABX, 4}, // Page Crossing + 1
    [0x79] = {"ADC", ADC, ABY, 4}, // Page Crossing + 1
    [0x61] = {"ADC", ADC, IZX, 6},
    [0x71] = {"ADC", ADC, IZY, 5}, // Page Crossing + 1

    /* SBC */
    [0xE9] = {"SBC", SBC, IMM, 2},
    [0xE5] = {"SBC", SBC, ZP0, 3},
    [0xF5] = {"SBC", SBC, ZPX, 4},
    [0xED] = {"SBC", SBC, ABS, 4},
    [0xFD] = {"SBC", SBC, ABX, 4}, // Page Crossing + 1
    [0xF9] = {"SBC", SBC, ABY, 4}, // Page Crossing + 1
    [0xE1] = {"SBC", SBC, IZX, 6},
    [0xF1] = {"SBC", SBC, IZY, 5}, // Page Crossing + 1

    /* INC */
    [0xE6] = {"INC", INC, ZP0, 5},
    [0xF6] = {"INC", INC, ZPX, 6},
    [0xEE] = {"INC", INC, ABS, 6},
    [0xFE] = {"INC", INC, ABX, 7},

    /* DEC */
    [0xC6] = {"DEC", DEC, ZP0, 5},
    [0xD6] = {"DEC", DEC, ZPX, 6},
    [0xCE] = {"DEC", DEC, ABS, 6},
    [0xDE] = {"DEC", DEC, ABX, 7},

    /* INX */
    [0xE8] = {"INX", INX, IMP, 2},

    /* DEX */
    [0xCA] = {"DEX", DEX, IMP, 2},

    /* INY */
    [0xC8] = {"INY", INY, IMP, 2},

    /* DEY */
    [0x88] = {"DEY", DEY, IMP, 2},

    /* ***************************************** */
    /*			Shift			 */
    /* ***************************************** */

    /* ASL */
    [0x0A] = {"ASL", ASL, ACC, 2},
    [0x06] = {"ASL", ASL, ZP0, 5},
    [0x16] = {"ASL", ASL, ZPX, 6},
    [0x0E] = {"ASL", ASL, ABS, 6},
    [0x1E] = {"ASL", ASL, ABX, 7},

    /* LSR */
    [0x4A] = {"LSR", LSR, ACC, 2},
    [0x46] = {"LSR", LSR, ZP0, 5},
    [0x56] = {"LSR", LSR, ZPX, 6},
    [0x4E] = {"LSR", LSR, ABS, 6},
    [0x5E] = {"LSR", LSR, ABX, 7},

    /* ROL */
    [0x2A] = {"ROL", ROL, ACC, 2},
    [0x26] = {"ROL", ROL, ZP0, 5},
    [0x36] = {"ROL", ROL, ZPX, 6},
    [0x2E] = {"ROL", ROL, ABS, 6},
    [0x3E] = {"ROL", ROL, ABX, 7},

    /* ROR */
    [0x6A] = {"ROR", ROR, ACC, 2},
    [0x66] = {"ROR", ROR, ZP0, 5},
    [0x76] = {"ROR", ROR, ZPX, 6},
    [0x6E] = {"ROR", ROR, ABS, 6},
    [0x7E] = {"ROR", ROR, ABX, 7},

    /* ***************************************** */
    /*			Bitwise			 */
    /* ***************************************** */

    /* AND */
    [0x29] = {"AND", AND, IMM, 2},
    [0x25] = {"AND", AND, ZP0, 3},
    [0x35] = {"AND", AND, ZPX, 4},
    [0x2D] = {"AND", AND, ABS, 4},
    [0x3D] = {"AND", AND, ABX, 4}, // Page Crossing + 1
    [0x39] = {"AND", AND, ABY, 4}, // Page Crossing + 1
    [0x21] = {"AND", AND, IZX, 6},
    [0x31] = {"AND", AND, IZY, 5}, // Page Crossing + 1

    /* ORA */
    [0x09] = {"ORA", ORA, IMM, 2},
    [0x05] = {"ORA", ORA, ZP0, 3},
    [0x15] = {"ORA", ORA, ZPX, 4},
    [0x0D] = {"ORA", ORA, ABS, 4},
    [0x1D] = {"ORA", ORA, ABX, 4}, // Page Crossing + 1
    [0x19] = {"ORA", ORA, ABY, 4}, // Page Crossing + 1
    [0x01] = {"ORA", ORA, IZX, 6},
    [0x11] = {"ORA", ORA, IZY, 5}, // Page Crossing + 1

    /* EOR */
    [0x49] = {"EOR", EOR, IMM, 2},
    [0x45] = {"EOR", EOR, ZP0, 3},
    [0x55] = {"EOR", EOR, ZPX, 4},
    [0x4D] = {"EOR", EOR, ABS, 4},
    [0x5D] = {"EOR", EOR, ABX, 4}, // Page Crossing + 1
    [0x59] = {"EOR", EOR, ABY, 4}, // Page Crossing + 1
    [0x41] = {"EOR", EOR, IZX, 6},
    [0x51] = {"EOR", EOR, IZY, 5}, // Page Crossing + 1

    /* BIT */
    [0x24] = {"BIT", BIT, ZP0, 3},
    [0x2C] = {"BIT", BIT, ABS, 4},

    /* ***************************************** */
    /*			Compare			 */
    /* ***************************************** */

    /* CMP */
    [0xC9] = {"CMP", CMP, IMM, 2},
    [0xC5] = {"CMP", CMP, ZP0, 3},
    [0xD5] = {"CMP", CMP, ZPX, 4},
    [0xCD] = {"CMP", CMP, ABS, 4},
    [0xDD] = {"CMP", CMP, ABX, 4}, // Page Crossing + 1
    [0xD9] = {"CMP", CMP, ABY, 4}, // Page Crossing + 1
    [0xC1] = {"CMP", CMP, IZX, 6},
    [0xD1] = {"CMP", CMP, IZY, 5}, // Page Crossing + 1

    /* CPX */
    [0xE0] = {"CPX", CPX, IMM, 2},
    [0xE4] = {"CPX", CPX, ZP0, 3},
    [0xEC] = {"CPX", CPX, ABS, 4},

    /* CPY */
    [0xC0] = {"CPY", CPY, IMM, 2},
    [0xC4] = {"CPY", CPY, ZP0, 3},
    [0xCC] = {"CPY", CPY, ABS, 4},

    /* ***************************************** */
    /*			Branch			 */
    /* ***************************************** */

    [0x90] = {"BCC", BCC, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0xB0] = {"BCS", BCS, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0xF0] = {"BEQ", BEQ, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0xD0] = {"BNE", BNE, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0x10] = {"BPL", BPL, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0x30] = {"BMI", BMI, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0x50] = {"BVC", BVC, REL, 2}, // +1 if branch taken, +2 if page crossed
    [0x70] = {"BVS", BVS, REL, 2}, // +1 if branch taken, +2 if page crossed

    /* ***************************************** */
    /*			Jump			 */
    /* ***************************************** */

    /* JMP */
    [0x4C] = {"JMP", JMP, ABS, 3},
    [0x6C] = {"JMP", JMP, IND, 5}, // Indirect - 페이지 경계 버그 주의

    /* JSR */
    [0x20] = {"JSR", JSR, ABS, 6},

    /* RTS */
    [0x60] = {"RTS", RTS, IMP, 6},

    /* BRK */
    [0x00] = {"BRK", BRK, IMP, 7},

    /* RTI */
    [0x40] = {"RTI", RTI, IMP, 6},

    /* ***************************************** */
    /*			Stack			 */
    /* ***************************************** */

    [0x48] = {"PHA", PHA, IMP, 3},
    [0x68] = {"PLA", PLA, IMP, 4},
    [0x08] = {"PHP", PHP, IMP, 3},
    [0x28] = {"PLP", PLP, IMP, 4},
    [0x9A] = {"TXS", TXS, IMP, 2},
    [0xBA] = {"TSX", TSX, IMP, 2},

    /* ***************************************** */
    /*			Flags			 */
    /* ***************************************** */

    [0x18] = {"CLC", CLC, IMP, 2},
    [0x38] = {"SEC", SEC, IMP, 2},
    [0x58] = {"CLI", CLI, IMP, 2},
    [0x78] = {"SEI", SEI, IMP, 2},
    [0xD8] = {"CLD", CLD, IMP, 2},
    [0xF8] = {"SED", SED, IMP, 2},
    [0xB8] = {"CLV", CLV, IMP, 2},

    /* ***************************************** */
    /*			Other			 */
    /* ***************************************** */

    [0xEA] = {"NOP", NOP, IMP, 2},
};
