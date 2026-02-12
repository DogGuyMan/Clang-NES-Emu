/**
 * @file input.h
 * @brief NES controller input interface.
 */
#ifndef NES_INPUT_H
#define NES_INPUT_H

#include "common/types.h"

typedef struct
{
	u8 buttons;
	u8 shift_reg;
} Controller;

void input_strobe(Controller *ctrl);
u8 input_read(Controller *ctrl);
void input_set_buttons(Controller *ctrl, u8 buttons);

#endif /* NES_INPUT_H */
