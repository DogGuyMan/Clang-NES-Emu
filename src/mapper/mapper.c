/**
 * @file mapper.c
 * @brief Mapper creation dispatcher.
 */
#include "mapper/mapper.h"
#include <stdlib.h>

/* Forward declarations for mapper constructors */
Mapper *mapper_000_create(ROM *rom);

Mapper *mapper_create(ROM *rom)
{
	int mapper_id = rom->mapper_id;
	switch (mapper_id)
	{
	case 0:
		return mapper_000_create(rom); // NROM
	case 1:
		return NULL; // ! TODO MMC1
	case 2:
		return NULL; // ! TODO UxROM
	case 3:
		return NULL; // ! TODO CNROM
	case 4:
		return NULL; // ! TODO MMC3
	default:
		return NULL;
	}
}
