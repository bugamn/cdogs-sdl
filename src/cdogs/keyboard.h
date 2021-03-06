/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.
    Copyright (C) 1995 Ronny Wester
    Copyright (C) 2003 Jeremy Chin
    Copyright (C) 2003-2007 Lucas Martin-King

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    This file incorporates work covered by the following copyright and
    permission notice:

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
#ifndef __KEYBOARD
#define __KEYBOARD

#include <SDL.h>

#define keySysReq       SDLK_SYSRQ
#define keyCapsLock -1
#define keyNumLock -1
#define keyScrollLock -1
#define keyLeftCtrl     SDLK_LCTRL
#define keyLeftAlt      SDLK_LALT
#define keyLeftShift    SDLK_LSHIFT
#define keyRightCtrl    SDLK_RCTRL
#define keyAltGr        SDLK_RALT
#define keyRightShift   SDLK_RSHIFT
#define keyEsc          SDLK_ESCAPE
#define keyBackspace    SDLK_BACKSPACE
#define keyEnter        SDLK_RETURN
#define keySpace        SDLK_SPACE
#define keyTab          SDLK_TAB
#define keyF1           SDLK_F1
#define keyF2           SDLK_F2
#define keyF3           SDLK_F3
#define keyF4           SDLK_F4
#define keyF5           SDLK_F5
#define keyF6           SDLK_F6
#define keyF7           SDLK_F7
#define keyF8           SDLK_F8
#define keyF9           SDLK_F9
#define keyF10          SDLK_F10
#define keyF11          SDLK_F11
#define keyF12          SDLK_F12
#define keyA            'a'
#define keyB            'b'
#define keyC            'c'
#define keyD            'd'
#define keyE            'e'
#define keyF            'f'
#define keyG            'g'
#define keyH            'h'
#define keyJ            'j'
#define keyK            'k'
#define keyL            'l'
#define keyM            'm'
#define keyN            'n'
#define keyO            'o'
#define keyP            'p'
#define keyQ            'q'
#define keyR            'r'
#define keyS            's'
#define keyT            't'
#define keyU            'u'
#define keyV            'v'
#define keyW            'w'
#define keyX            'x'
#define keyY            'y'
#define keyZ            'z'
#define key1            '1'
#define key2            '2'
#define key3            '3'
#define key4            '4'
#define key5            '5'
#define key6            '6'
#define key7            '7'
#define key8            '8'
#define key9            '9'
#define key0            '0'
#define keyMinus        '-'
#define keyEqual        '='
#define keyLBracket     '['
#define keyRBracket     ']'
#define keySemicolon    ';'
#define keyTick         '`'
#define keyApostrophe   '\''
#define keyBackslash    '\\'
#define keyComma        ','
#define keyPeriod       '.'
#define keySlash        '/'
#define keyInsert       SDLK_INSERT
#define keyDelete       SDLK_DELETE
#define keyHome         SDLK_HOME
#define keyEnd          SDLK_END
#define keyPageUp       SDLK_PAGEUP
#define keyArrowLeft    SDLK_LEFT
#define keyArrowRight   SDLK_RIGHT
#define keyArrowUp      SDLK_UP
#define keyArrowDown    SDLK_DOWN
#define keyKeypad0      SDLK_KP0
#define keyKeypad1      SDLK_KP1
#define keyKeypad2      SDLK_KP2
#define keyKeypad3      SDLK_KP3
#define keyKeypad4      SDLK_KP4
#define keyKeypad5      SDLK_KP5
#define keyKeypad6      SDLK_KP6
#define keyKeypad7      SDLK_KP7
#define keyKeypad8      SDLK_KP8
#define keyKeypad9      SDLK_KP9
#define keyKeypadStar   SDLK_KP_MULTIPLY
#define keyKeypadMinus  SDLK_KP_MINUS
#define keyKeypadPlus   SDLK_KP_PLUS
#define keyKeypadEnter  SDLK_KP_ENTER
#define keyKeypadSlash  SDLK_KPDIVIDE

typedef struct
{
	SDL_Event keyevent;
	int previous_keys[512];
	int current_keys[512];
} keyboard_t;
extern keyboard_t gKeyboard;

void KeyInit(keyboard_t *keyboard);
void KeyPoll(keyboard_t *keyboard);
int KeyIsDown(keyboard_t *keyboard, int key);
int KeyIsPressed(keyboard_t *keyboard, int key);
int KeyIsReleased(keyboard_t *keyboard, int key);
int KeyGetPressed(keyboard_t *keyboard);

#endif
