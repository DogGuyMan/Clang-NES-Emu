/**
 * @file mapper_000.c
 * @brief NROM (Mapper 0) implementation.
 */
#include "mapper/mapper.h"
#include <common/log.h>
#include <rom/rom.h>
#include <stdlib.h>
#include <string.h>

/*
1. NROM 상태 구조체 설계
2. mapper_000_cpu_read 구현
3. mapper_000_cpu_write 구현
4. mapper_000_ppu_read 구현
5. mapper_000_ppu_write 구현
6. 나머지 인터페이스 함수
7. mapper_000_create 구현
8. mapper.c의 mapper_create 연결
*/
typedef struct Mapper000State Mapper000State;
void mapper_free(Mapper *m);
static void *state_create(ROM *rom);
static void state_free(Mapper000State *this);
static u8 cpu_read(Mapper *m, u16 addr);
static void cpu_write(Mapper *m, u16 addr, u8 val);
static u8 ppu_read(Mapper *m, u16 addr);
static void ppu_write(Mapper *m, u16 addr, u8 val);
static u8 get_mirroring(struct Mapper *m);
static bool irq_pending(struct Mapper *m);
static void scanline_counter(struct Mapper *m);

typedef struct Mapper000State
{
	u8 *prg_rom_ptr;
	u32 prg_size;
	u8 *chr_data_ptr;
	u32 chr_size;
	bool is_chr_ram;
	bool is_32kb;
	u8 mirroring;
	void (*const free)(Mapper000State *this);
} Mapper000State;

static const Mapper EMPTY_MAPPER_000_TEMPLATE = {
    .id = 0,
    .state = NULL,

    .cpu_read = cpu_read,
    .cpu_write = cpu_write,
    .ppu_read = ppu_read,
    .ppu_write = ppu_write,

    .get_mirroring = get_mirroring,
    .irq_pending = irq_pending,
    .scanline_counter = scanline_counter,
    .free = mapper_free,
};

static const Mapper000State EMPTY_MAPPER_000_STATE_TEMPLATE = {
    .prg_rom_ptr = NULL,
    .prg_size = 0,
    .chr_data_ptr = NULL,
    .chr_size = 0,
    .is_chr_ram = false,
    .is_32kb = false,
    .mirroring = 0,
    .free = state_free,
};

Mapper *mapper_000_create(ROM *rom)
{
	/* TODO: implement NROM mapper */
	Mapper *temp_mapper = NULL;
	void *temp_state = NULL;

	temp_mapper = malloc(sizeof(Mapper));
	if (temp_mapper == NULL)
	{
		log_msg(LOG_ERROR, "Mapper 0 할당 실패");
		goto cleanup;
	}

	memcpy(temp_mapper, &EMPTY_MAPPER_000_TEMPLATE, sizeof(Mapper));
	temp_state = state_create(rom);
	if (temp_state == NULL)
	{
		log_msg(LOG_ERROR, "Mapper 0 State 할당 실패");
		goto cleanup;
	}
	temp_mapper->state = temp_state;
	return temp_mapper;

cleanup:
	if (temp_mapper != NULL)
		free(temp_mapper);
	if (temp_state != NULL)
		free(temp_state);
	return NULL;
}

void mapper_free(Mapper *m)
{
	if (m != NULL)
	{
		if (m->state != NULL)
		{
			Mapper000State *state_ptr = GET_MAPPER_STATE(Mapper000State, m); //(Mapper000State *)m->state;
			state_ptr->free(state_ptr);
		}
		free(m);
	}
}

static void *state_create(ROM *rom)
{
	Mapper000State *temp_mapper_state = malloc(sizeof(Mapper000State));
	u8 *ram_chr_data = NULL;

	if (temp_mapper_state == NULL)
	{
		log_msg(LOG_ERROR, "Mapper 0 State 할당 실패");
		goto cleanup;
	}
	memcpy(temp_mapper_state, &EMPTY_MAPPER_000_STATE_TEMPLATE, sizeof(Mapper000State));
	temp_mapper_state->prg_rom_ptr = rom->prg_rom_ptr;
	temp_mapper_state->prg_size = ROM_PRG_BANK_SIZE * rom->header.prg_rom_size;
	if (rom->header.prg_rom_size == 2)
		temp_mapper_state->is_32kb = true;

	if (rom->header.chr_rom_size > 0) // ROM일때
	{
		temp_mapper_state->chr_data_ptr = rom->chr_rom_ptr;
		temp_mapper_state->chr_size = ROM_CHR_BANK_SIZE * rom->header.chr_rom_size;
		temp_mapper_state->is_chr_ram = false;
	}
	else // RAM일때.
	{
		ram_chr_data = malloc(ROM_CHR_BANK_SIZE);
		if (ram_chr_data == NULL)
		{
			log_msg(LOG_ERROR, "RAM CHR 할당 실패");
			goto cleanup;
		}
		temp_mapper_state->chr_data_ptr = ram_chr_data;
		temp_mapper_state->chr_size = ROM_CHR_BANK_SIZE;
		temp_mapper_state->is_chr_ram = true;
	}

	temp_mapper_state->mirroring = (rom->header.mapper_lower_flags.flags.nametable_arrangement & NAMETABLE_ARRANGEMENT_VERTICAL_FLAG);
	return temp_mapper_state;

cleanup:
	if (temp_mapper_state != NULL)
		free(temp_mapper_state);
	if (ram_chr_data != NULL)
		free(ram_chr_data);
	return NULL;
}

static void state_free(Mapper000State *this)
{
	if (this != NULL)
	{
		if (this->is_chr_ram && this->chr_data_ptr != NULL)
			free(this->chr_data_ptr);
		free(this);
	}
}

// 1000 0000 0000 0000
#define PRG_ADDRESS_OFFSET 0x8000

// 0011 1111 1111 1111
// 01XX XXXX XXXX XXXX -> 00XX XXXX XXXX XXXX
#define PRG_16K_MIRROR_FLAG 0x3FFF

// 0111 1111 1111 1111
// 01XX XXXX XXXX XXXX -> 01XX XXXX XXXX XXXX
#define PRG_32K_MIRROR_FLAG 0x7FFF

static u8 cpu_read(Mapper *m, u16 addr)
{
	// 어차핀 Unsined 이므로..
	if (addr < PRG_ADDRESS_OFFSET)
		return 0;
	u16 offseted_addr = addr - PRG_ADDRESS_OFFSET;

	Mapper000State *state = GET_MAPPER_STATE(Mapper000State, m);
	if (!state->is_32kb)
		offseted_addr &= PRG_16K_MIRROR_FLAG;
	return *(state->prg_rom_ptr + offseted_addr);
}

#define PPU_ADDRESS_END 0x1FFF

static void cpu_write(Mapper *m, u16 addr, u8 val)
{
	return;
}

static u8 ppu_read(Mapper *m, u16 addr)
{
	if (PPU_ADDRESS_END < addr)
		return 0;

	Mapper000State *state = GET_MAPPER_STATE(Mapper000State, m);
	return *(state->chr_data_ptr + addr);
}

static void ppu_write(Mapper *m, u16 addr, u8 val) // ! TODO
{
	if (PPU_ADDRESS_END < addr)
		return;
	Mapper000State *state = GET_MAPPER_STATE(Mapper000State, m);
	if (state->is_chr_ram)
	{
		*(state->chr_data_ptr + addr) = val;
	}
}

static u8 get_mirroring(Mapper *m)
{
	return GET_MAPPER_STATE(Mapper000State, m)->mirroring;
}

static bool irq_pending(Mapper *m)
{
	return false;
}

static void scanline_counter(Mapper *m)
{
	return;
}
