#include "common/log.h"
#include "common/types.h"
#include "rom/rom.h"

void check_rom_byte_padding(void)
{
	log_msg(LOG_INFO, "ROMHeader Size : %lu", sizeof(ROMHeader));
	log_msg(LOG_INFO, "Flags6 Size : %lu", sizeof(Flags6));
	log_msg(LOG_INFO, "Flags7 Size : %lu", sizeof(Flags7));
}

int main(int argc, char *argv[])
{
	log_set_level(LOG_INFO);
	check_rom_byte_padding();
	return 0;
}
