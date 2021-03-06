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
#include "utils.h"

#include <math.h>
#include <string.h>

int debug = 0;
int debug_level = D_NORMAL;

double ToDegrees(double radians)
{
	return radians * 180.0 / PI;
}

void CalcChebyshevDistanceAndBearing(
	Vector2i origin, Vector2i target, int *distance, int *bearing)
{
	// short circuit if origin and target same
	if (origin.x == target.x && origin.y == target.y)
	{
		*distance = 0;
		*bearing = 0;
	}
	else
	{
		double angle;
		*distance = CHEBYSHEV_DISTANCE(origin.x, origin.y, target.x, target.y);
		angle = ToDegrees(atan2(target.y - origin.y, target.x - origin.x));
		// convert angle to bearings
		// first rotate so 0 angle = 0 bearing
		angle -= 90.0;
		// then reflect about Y axis
		angle = 360 - angle;
		*bearing = (int)floor(angle + 0.5);
	}
}

char *InputDeviceStr(int d)
{
	switch (d)
	{
	case INPUT_DEVICE_KEYBOARD:
		return "Keyboard";
	case INPUT_DEVICE_JOYSTICK_1:
		return "Joystick 1";
	case INPUT_DEVICE_JOYSTICK_2:
		return "Joystick 2";
	default:
		return "";
	}
}
input_device_e StrInputDevice(const char *str)
{
	if (strcmp(str, "Keyboard") == 0)
	{
		return INPUT_DEVICE_KEYBOARD;
	}
	else if (strcmp(str, "Joystick 1") == 0)
	{
		return INPUT_DEVICE_JOYSTICK_1;
	}
	else if (strcmp(str, "Joystick 1") == 0)
	{
		return INPUT_DEVICE_JOYSTICK_2;
	}
	else
	{
		return INPUT_DEVICE_KEYBOARD;
	}
}
