/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.

    Copyright (c) 2013, Cong Xu
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __JOYSTICK
#define __JOYSTICK

#include <SDL_joystick.h>


typedef struct
{
	SDL_Joystick *j;
	int x;
	int y;
	int currentButtonsField;
	int previousButtonsField;
	int numButtons;
	int numAxes;
	int numHats;
} joystick_t;

#define MAX_JOYSTICKS 10
typedef struct
{
	int numJoys;
	joystick_t joys[MAX_JOYSTICKS];
} joysticks_t;
extern joysticks_t gJoysticks;

void JoyInit(joysticks_t *joys);
void JoyReset(joysticks_t *joys);
void GJoyReset(void);
void JoyTerminate(joysticks_t *joys);
void JoyPoll(joysticks_t *joys);

int JoyIsDown(joystick_t *joystick, int button);
int JoyIsPressed(joystick_t *joystick, int button);
int JoyIsAnyPressed(joystick_t *joystick);

#endif
