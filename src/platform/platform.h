/**
 * @file platform.h
 * @brief SDL2 platform frontend interface.
 */
#ifndef NES_PLATFORM_H
#define NES_PLATFORM_H

#include "common/types.h"
#include "input/input.h"
#include <SDL.h>

typedef struct {
    SDL_Window       *window;
    SDL_Renderer     *renderer;
    SDL_Texture      *texture;
    SDL_AudioDeviceID audio_device;
} Platform;

bool platform_init(Platform *p, int scale);
void platform_render_frame(Platform *p, u32 *framebuffer);
void platform_poll_input(Platform *p, Controller *ctrl1, Controller *ctrl2);
void platform_queue_audio(Platform *p, float *samples, u32 count);
void platform_destroy(Platform *p);

#endif /* NES_PLATFORM_H */
