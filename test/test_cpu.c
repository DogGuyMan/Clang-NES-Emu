/**
 * @file test_cpu.c
 * @brief CPU test harness — runs nestest.nes in headless mode.
 */
#include "common/log.h"
#include "common/types.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: test_cpu <nestest.nes>\n");
		return 1;
	}

	log_set_level(LOG_DEBUG);
	LOG_INFO("CPU test: %s", argv[1]);

	/* TODO: load ROM, init CPU at PC=$C000, run and compare logs */

	LOG_INFO("CPU test stub — not yet implemented");
	return 0;
}
