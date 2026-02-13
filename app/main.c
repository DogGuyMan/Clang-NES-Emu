/**
 * @file main.c
 * @brief NES emulator entry point.
 */
#include "common/log.h"
#include "common/types.h"
#include "rom/rom.h"

void rom_byte_padding(void);
void test_endian(void);

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	log_set_level(LOG_INFO);
	LOG_INFO("nes-emulator v0.1.0");

	// rom_byte_padding();
	test_endian();

	return 0;
}

void rom_byte_padding(void)
{
	log_msg(LOG_INFO, "ROMHeader Size : %lu", sizeof(ROMHeader));
	log_msg(LOG_INFO, "Flags6 Size : %lu", sizeof(Flags6));
	log_msg(LOG_INFO, "Flags7 Size : %lu", sizeof(Flags7));
}

void test_endian(void)
{
	unsigned int x = 0x12345678;
	char *c = (char *)&x;
	if (*c == 0x78)				      // 뒤에서 부터 파싱이 된다면..
		log_msg(LOG_INFO, "Little-endian\n"); // ✅
	else if (*c == 0x12)			      // 앞에서 부터 파싱이 된다면.
		log_msg(LOG_INFO, "Big-endian\n");
	return;
}
