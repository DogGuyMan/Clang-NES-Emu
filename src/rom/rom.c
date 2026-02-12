/**
 * @file rom.c
 * @brief iNES ROM parser implementation.
 */
#include "rom/rom.h"

bool rom_load(ROM *rom, const char *filepath) {
    (void)rom;
    (void)filepath;
    /* TODO: implement iNES parser */
    return false;
}

void rom_free(ROM *rom) {
    (void)rom;
    /* TODO: free allocated ROM data */
}
