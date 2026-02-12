/**
 * @file mapper.c
 * @brief Mapper creation dispatcher.
 */
#include "mapper/mapper.h"
#include <stdlib.h>

/* Forward declarations for mapper constructors */
Mapper *mapper_000_create(ROM *rom);

Mapper *mapper_create(ROM *rom) {
    switch (rom->mapper_id) {
        case 0:  return mapper_000_create(rom);
        default: return NULL;
    }
}
