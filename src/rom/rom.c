/**
 * @file rom.c
 * @brief iNES ROM parser implementation.
 */
#include "rom/rom.h"
#include "common/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define iNES

/*
1. 파일 열기 및 에러 처리
2. 16바이트 헤더 읽기
3. 매직 넘버 검증 ($4E $45 $53 $1A)
4. 오염된 헤더 감지 — 바이트 12-15가 모두 0이 아니면서 NES 2.0도 아닌 경우,
	매퍼 상위 니블을 신뢰할 수 없음 (스펙의 "권장 감지 절차" 참고)
5. 트레이너 존재 시 512바이트 읽기
6. PRG ROM 데이터 할당 및 읽기 (단위 → 바이트 변환)
7. CHR ROM 데이터 할당 및 읽기 (크기가 0이면 건너뛰기)
8. 파일 닫기
*/

static const ROM EMPTY_ROM_TEMPLATE = {
    .header = {
	0,
    },
    .mapper_id = 0,
    .trainer_rom_ptr = NULL,
    .prg_rom_ptr = NULL,
    .chr_rom_ptr = NULL,
    .rom_free = rom_free,
};

ROM *rom_create(void)
{
	ROM *temp_rom = malloc(sizeof(ROM));
	if (temp_rom == NULL)
	{
		log_msg(LOG_ERROR, "롬 메모리 할당 실패");
		return NULL;
	}
	memcpy(temp_rom, &EMPTY_ROM_TEMPLATE, sizeof(ROM));
	return temp_rom;
}

bool rom_load(ROM *rom, const char *filepath)
{
	bool is_load_success = true;
	bool is_ines_ver_1 = true;
	// 1. 파일 리딩
	FILE *ROM_FILE = fopen(filepath, "rb");
	ROMHeader *header_ptr = &(rom->header);

	if (ROM_FILE == NULL)
	{
		log_msg(LOG_ERROR, "롬 파일이 없음 -> 종료");
		is_load_success = false;
		goto cleanup;
	}

	// 2. 헤더 읽기
	{
		u64 read_count = fread(&(rom->header), ROM_HEADER_SIZE, 1UL, ROM_FILE);
		if (read_count <= 0)
		{
			log_msg(LOG_ERROR, "헤더 읽기 실패 -> 종료");
			is_load_success = false;
			goto cleanup;
		}
	}

	// 3. 매직넘버 검증
	{
		u8 *magic_numbers = header_ptr->magic_numbers;
		if (!(magic_numbers[0] == 'N' && magic_numbers[1] == 'E' && magic_numbers[2] == 'S' && magic_numbers[3] == 0x1A))
		{
			log_msg(LOG_ERROR, "매직넘버 검증 -> 종료");
			is_load_success = false;
			goto cleanup;
		}
	}

#ifdef iNES
	// 4. 오염된 헤더 및 매퍼 생성

	// 비트 필드를 사용하면 이렇게.
	// is_ines_ver_1 &= (header_ptr->mapper_upper_flags.flags.nes_2_id == 0);

	// 하지만 이런 방법을 사용하면 이식성이 보장된단다.. 00001100
	is_ines_ver_1 &= ((header_ptr->mapper_upper_flags.raw & 0x0C) == 0);
	is_ines_ver_1 &= (header_ptr->unused_pad_2 == 0);
	is_ines_ver_1 &= (header_ptr->unused_pad_3 == 0);
	is_ines_ver_1 &= (header_ptr->unused_pad_4 == 0);
	is_ines_ver_1 &= (header_ptr->unused_pad_5 == 0);

	// rom->mapper_id = (header_ptr->mapper_lower_flags.flags.mapper_lower_nibble);
	rom->mapper_id = ((header_ptr->mapper_lower_flags.raw >> 4) & 0x0F);
	if (is_ines_ver_1)
	{
		// rom->mapper_id |= (header_ptr->mapper_upper_flags.flags.mapper_upper_nibble) << 4;
		rom->mapper_id |= (header_ptr->mapper_upper_flags.raw & 0xF0);
	}
#endif
	// 5. 트레이너 존재 시 512바이트 읽기
	// if (header_ptr->mapper_lower_flags.flags.has_trainer)
	if (header_ptr->mapper_lower_flags.raw & 0x04)
	{
		rom->trainer_rom_ptr = malloc(ROM_TRAINER_SIZE);
		if (rom->trainer_rom_ptr == NULL)
		{
			log_msg(LOG_ERROR, "트레이너 동적할당 실패");
			is_load_success = false;
			goto cleanup;
		}

		u64 read_count = fread(rom->trainer_rom_ptr, ROM_TRAINER_SIZE, 1UL, ROM_FILE);
		if (read_count <= 0)
		{
			is_load_success = false;
			goto cleanup;
		}
	}

	// 6. PRG ROM 데이터 할당 및 읽기 (단위 → 바이트 변환)
	{
		int prg_bank_cnt = header_ptr->prg_rom_size;
		rom->prg_rom_ptr = malloc(ROM_PRG_BANK_SIZE * prg_bank_cnt);
		if (rom->prg_rom_ptr == NULL)
		{
			log_msg(LOG_ERROR, "PRG 자원 동적할당 실패");
			is_load_success = false;
			goto cleanup;
		}
		u64 read_count = fread(rom->prg_rom_ptr, ROM_PRG_BANK_SIZE * prg_bank_cnt, 1UL, ROM_FILE);
		if (read_count <= 0)
		{
			is_load_success = false;
			goto cleanup;
		}
	}
	// 7. CHR ROM 데이터 할당 및 읽기 (크기가 0이면 건너뛰기)

	if (header_ptr->chr_rom_size > 0)
	{
		int chr_bank_cnt = header_ptr->chr_rom_size;
		rom->chr_rom_ptr = malloc(ROM_CHR_BANK_SIZE * chr_bank_cnt);
		if (rom->chr_rom_ptr == NULL)
		{
			log_msg(LOG_ERROR, "CHR 자원 동적할당 실패");
			is_load_success = false;
			goto cleanup;
		}

		u64 read_count = fread(rom->chr_rom_ptr, ROM_CHR_BANK_SIZE * chr_bank_cnt, 1UL, ROM_FILE);
		if (read_count <= 0)
		{
			is_load_success = false;
			goto cleanup;
		}
	}

cleanup:
	if (ROM_FILE != NULL)
		fclose(ROM_FILE);
	return is_load_success;
}

void rom_free(ROM *rom)
{
	if (rom != NULL)
	{
		if (rom->chr_rom_ptr != NULL)
			free(rom->chr_rom_ptr);
		if (rom->prg_rom_ptr != NULL)
			free(rom->prg_rom_ptr);
		if (rom->trainer_rom_ptr != NULL)
			free(rom->trainer_rom_ptr);
		free(rom);
	}
}
