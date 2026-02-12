/**
 * @file main.c
 * @brief NES emulator entry point.
 */
#include "common/log.h"
#include "common/types.h"
#include "rom/rom.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	log_set_level(LOG_INFO);
	LOG_INFO("nes-emulator v0.1.0");
	log_msg(LOG_INFO, "NES_HEADER Size : %lu", sizeof(NES_HEADER));
	log_msg(LOG_INFO, "Flags6 Size : %lu", sizeof(Flags6));
	log_msg(LOG_INFO, "Flags7 Size : %lu", sizeof(Flags7));

	return 0;
}
