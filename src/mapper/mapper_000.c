/**
 * @file mapper_000.c
 * @brief NROM (Mapper 0) implementation.
 */
#include "mapper/mapper.h"
#include <common/log.h>
#include <rom/rom.h>
#include <stdlib.h>

/*
1. NROM 상태 구조체 설계
	PRG ROM 포인터 및 크기 저장
	CHR ROM/RAM 포인터 및 크기 저장
	미러링 모드 저장 (ROM 헤더에서 가져옴)
	16KB vs 32KB PRG 구분 플래그
	* 매퍼의 상태를 말하는것은. 뱅크 스위칭 레지스터가 없고, 런타임에 변하는 상태가 없다.
	* MMC1이나 MMC3 같은 매퍼는 CPU가 특정 주소에 값을 쓰면 내부 레지스터가 바뀌고 뱅크 매핑이 변경되지만, NROM에는 그런 레지스터 자체가 존재하지 않는다.
2. mapper_000_cpu_read 구현
	주소 범위 $8000-$FFFF → PRG ROM
	PRG 크기에 따른 매핑:
	16KB: $8000-$BFFF와 $C000-$FFFF가 동일한 16KB에 미러링
	32KB: 직접 매핑
3. mapper_000_cpu_write 구현
	NROM은 쓰기 불가 (no-op)
4. mapper_000_ppu_read 구현
	주소 범위 $0000-$1FFF → CHR ROM/RAM
	CHR ROM 존재 시 ROM에서 읽기
	CHR RAM인 경우 RAM에서 읽기
5. mapper_000_ppu_write 구현
	CHR ROM: no-op (ROM은 쓰기 불가)
	CHR RAM: RAM에 쓰기
6. 나머지 인터페이스 함수
	get_mirroring: ROM 헤더의 미러링 모드 반환
	irq_pending: 항상 false (NROM은 IRQ 없음)
	scanline_counter: no-op
	free: state 및 CHR RAM(있다면) 해제
7. mapper_000_create 구현
	Mapper 구조체 할당 및 초기화
	모든 함수 포인터 설정
	ROM 데이터 복사
	CHR RAM 할당 (chr_rom_size == 0인 경우)
8. mapper.c의 mapper_create 연결
	mapper_id == 0일 때 mapper_000_create 호출
*/

static void mapper_free(Mapper *m);
static u8 cpu_read(Mapper *m, u16 addr);
static void cpu_write(Mapper *m, u16 addr, u8 val);
static u8 ppu_read(Mapper *m, u16 addr);
static void ppu_write(Mapper *m, u16 addr, u8 val);

typedef struct Mapper000State
{
	u8 *prg_rom_ptr;
	u32 prg_size;
	u8 *chr_data_ptr;
	u32 chr_size;
	bool is_chr_ram;
	bool is_32kb;
	u8 mirroring;
} Mapper000State;

static const Mapper EMPTY_MAPPER_000_TEMPLATE = {
    .id = 0,
    .state = NULL,

    .cpu_read = cpu_read,
    .cpu_write = cpu_write,
    .ppu_read = ppu_read,
    .ppu_write = ppu_write,

    .get_mirroring = NULL,    // ! TODO
    .irq_pending = NULL,      // ! TODO
    .scanline_counter = NULL, // ! TODO
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
};

Mapper *mapper_000_create(ROM *rom)
{
	/* TODO: implement NROM mapper */
	Mapper *temp_mapper = malloc(sizeof(Mapper));
	Mapper000State *temp_mapper_state = malloc(sizeof(Mapper000State));
	u8 *ram_chr_data = NULL;

	if (temp_mapper == NULL)
	{
		log_msg(LOG_ERROR, "Mapper 0 할당 실패");
		goto cleanup;
	}
	if (temp_mapper_state == NULL)
	{
		log_msg(LOG_ERROR, "Mapper 0 State 할당 실패");
		goto cleanup;
	}
	memcpy(temp_mapper, &EMPTY_MAPPER_000_TEMPLATE, sizeof(Mapper));
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

	temp_mapper->state = (void *)temp_mapper_state;
	return temp_mapper;

cleanup:
	if (temp_mapper != NULL)
		free(temp_mapper);
	if (temp_mapper_state != NULL)
		free(temp_mapper_state);
	if (ram_chr_data != NULL)
		free(ram_chr_data);
	return NULL;
}

static void mapper_free(Mapper *m)
{
	if (m != NULL)
	{
		if (m->state != NULL)
		{
			Mapper000State *state_ptr = (Mapper000State *)m->state;
			if (state_ptr->is_chr_ram)
				free(state_ptr->chr_data_ptr);
			free(state_ptr);
		}
		free(m);
	}
}

static u8 cpu_read(Mapper *m, u16 addr) // ! TODO
{
}

static void cpu_write(Mapper *m, u16 addr, u8 val) // ! TODO
{
}

static u8 ppu_read(Mapper *m, u16 addr) // ! TODO
{
}

static void ppu_write(Mapper *m, u16 addr, u8 val) // ! TODO
{
}
