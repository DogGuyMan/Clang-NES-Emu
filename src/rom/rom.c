/**
 * @file rom.c
 * @brief iNES ROM parser implementation.
 */
#include "rom/rom.h"

bool rom_load(ROM *rom, const char *filepath)
{
	bool load_flag = true;
	FILE *ROM_FILE = fopen(filepath, "rb");
	if (ROM_FILE == NULL)
	{
		printf("롬 파일이 없음 -> 종료");
		load_flag = false;
		goto cleanup;
	}

	int read_count = fread(&(rom->header), sizeof(NES_HEADER), 1UL, ROM_FILE);
	if (read_count <= 0)
	{
		printf("헤더 읽기 실패");
		load_flag = false;
		goto cleanup;
	}
cleanup:
	fclose(ROM_FILE);
	return load_flag;
}

void rom_free(ROM *rom)
{
	(void)rom;
	/* TODO: free allocated ROM data */
}
