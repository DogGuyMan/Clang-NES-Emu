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

	return 0;
}
