#include "common/log.h"
#include <stdio.h>

void check_endian(void)
{
	unsigned int x = 0x12345678;
	char *c = (char *)&x;
	if (*c == 0x78)				      // 뒤에서 부터 파싱이 된다면..
		log_msg(LOG_INFO, "Little-endian\n"); // ✅
	else if (*c == 0x12)			      // 앞에서 부터 파싱이 된다면.
		log_msg(LOG_INFO, "Big-endian\n");
	return;
}

int main(int argc, char *argv[])
{
	log_set_level(LOG_INFO);
	check_endian();
	return 0;
}
