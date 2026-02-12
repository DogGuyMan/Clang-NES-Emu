/**
 * @file platform.c
 * @brief SDL2 platform frontend implementation.
 */
#include "platform/platform.h"

bool platform_init(Platform *p, int scale)
{
	(void)p;
	(void)scale;
	/* TODO: implement */
	return false;
}

void platform_render_frame(Platform *p, u32 *framebuffer)
{
	(void)p;
	(void)framebuffer;
	/* TODO: implement */
}

void platform_poll_input(Platform *p, Controller *ctrl1, Controller *ctrl2)
{
	(void)p;
	(void)ctrl1;
	(void)ctrl2;
	/* TODO: implement */
}

void platform_queue_audio(Platform *p, float *samples, u32 count)
{
	(void)p;
	(void)samples;
	(void)count;
	/* TODO: implement */
}

void platform_destroy(Platform *p)
{
	(void)p;
	/* TODO: implement */
}
