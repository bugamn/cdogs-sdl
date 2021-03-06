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
#include "sounds.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <SDL.h>

#include "files.h"
#include "music.h"

SoundDevice gSoundDevice =
{
	0,
	NULL,
	MUSIC_OK,
	"",
	{0, 0},
	{0, 0},
	{
		{"sounds/booom.wav",		0,	NULL},
		{"sounds/launch.wav",		0,	NULL},
		{"sounds/mg.wav",			0,	NULL},
		{"sounds/flamer.wav",		0,	NULL},
		{"sounds/shotgun.wav",		0,	NULL},
		{"sounds/fusion.wav",		0,	NULL},
		{"sounds/switch.wav",		0,	NULL},
		{"sounds/scream.wav",		0,	NULL},
		{"sounds/aargh1.wav",		0,	NULL},
		{"sounds/aargh2.wav",		0,	NULL},
		{"sounds/aargh3.wav",		0,	NULL},
		{"sounds/hahaha.wav",		0,	NULL},
		{"sounds/bang.wav",			0,	NULL},
		{"sounds/pickup.wav",		0,	NULL},
		{"sounds/click.wav",		0,	NULL},
		{"sounds/whistle.wav",		0,	NULL},
		{"sounds/powergun.wav",		0,	NULL},
		{"sounds/mg.wav",			0,	NULL},
		{"sounds/shotgun_r.wav",	0,	NULL},
		{"sounds/powergun_r.wav",	0,	NULL},
		{"sounds/package_r.wav",	0,	NULL},
		{"sounds/knife_flesh.wav",	0,	NULL},
		{"sounds/knife_hard.wav",	0,	NULL},
		{"sounds/hit_fire.wav",		0,	NULL},
		{"sounds/hit_flesh.wav",	0,	NULL},
		{"sounds/hit_gas.wav",		0,	NULL},
		{"sounds/hit_hard.wav",		0,	NULL},
		{"sounds/hit_petrify.wav",	0,	NULL},
		{"sounds/footstep.wav",		0,	NULL},
		{"sounds/slide.wav",		0,	NULL}
	}
};


int OpenAudio(int frequency, Uint16 format, int channels, int chunkSize)
{
	int qFrequency;
	Uint16 qFormat;
	int qChannels;

	if (Mix_OpenAudio(frequency, format, channels, chunkSize) != 0)
	{
		printf("Couldn't open audio!: %s\n", SDL_GetError());
		return 1;
	}

	// Check that we got the specs we wanted
	Mix_QuerySpec(&qFrequency, &qFormat, &qChannels);
	debug(D_NORMAL, "spec: f=%d fmt=%d c=%d\n", qFrequency, qFormat, qChannels);
	if (qFrequency != frequency || qFormat != format || qChannels != channels)
	{
		printf("Audio not what we want.\n");
		return 1;
	}

	return 0;
}

void LoadSound(SoundData *sound)
{
	struct stat st;

	sound->isLoaded = 0;

	// Check that file exists
	if (stat(GetDataFilePath(sound->name), &st) == -1)
	{
		printf("Error finding sample '%s'\n", GetDataFilePath(sound->name));
		return;
	}

	// Load file data
	if ((sound->data = Mix_LoadWAV(GetDataFilePath(sound->name))) == NULL)
	{
		printf("Error loading sample '%s'\n", GetDataFilePath(sound->name));
		return;
	}

	sound->isLoaded = 1;
}

void SoundInitialize(SoundDevice *device, SoundConfig *config)
{
	int i;

	if (OpenAudio(22050, AUDIO_S16, 2, 512) != 0)
	{
		return;
	}

	SoundReconfigure(device, config);

	for (i = 0; i < SND_COUNT; i++)
	{
		LoadSound(&device->sounds[i]);
	}
}

void SoundReconfigure(SoundDevice *device, SoundConfig *config)
{
	device->isInitialised = 0;

	if (Mix_AllocateChannels(config->SoundChannels) != config->SoundChannels)
	{
		printf("Couldn't allocate channels!\n");
		return;
	}

	Mix_Volume(-1, config->SoundVolume);
	Mix_VolumeMusic(config->MusicVolume);
	if (config->MusicVolume > 0)
	{
		MusicResume(device);
	}
	else
	{
		MusicPause(device);
	}

	device->isInitialised = 1;
}

void SoundTerminate(SoundDevice *device, int isWaitingUntilSoundsComplete)
{
	int i;
	if (!device->isInitialised)
	{
		return;
	}

	debug(D_NORMAL, "shutting down sound\n");
	if (isWaitingUntilSoundsComplete)
	{
		Uint32 waitStart = SDL_GetTicks();
		while (Mix_Playing(-1) > 0 &&
			SDL_GetTicks() - waitStart < 1000);
	}
	MusicStop(device);
	Mix_CloseAudio();
	for (i = 0; i < SND_COUNT; i++)
	{
		if (device->sounds[i].isLoaded)
		{
			Mix_FreeChunk(device->sounds[i].data);
			device->sounds[i].data = NULL;
		}
	}
}

void SoundPlayAtPosition(
	SoundDevice *device, sound_e sound, int distance, int bearing)
{
	int channel;
	distance /= 2;
	// Don't play anything if it's too distant
	// This means we don't waste sound channels
	if (distance > 255)
	{
		return;
	}

	if (!device->isInitialised)
	{
		return;
	}

	debug(D_VERBOSE, "sound: %d distance: %d bearing: %d\n",
		sound, distance, bearing);

	channel = Mix_PlayChannel(-1, device->sounds[sound].data , 0);
	Mix_SetPosition(channel, (Sint16)bearing, (Uint8)distance);
}

void SoundPlay(SoundDevice *device, sound_e sound)
{
	if (!device->isInitialised)
	{
		return;
	}

	SoundPlayAtPosition(device, sound, 0, 0);
}


void SoundSetLeftEar(int x, int y)
{
	gSoundDevice.earLeft.x = x;
	gSoundDevice.earLeft.y = y;
}

void SoundSetRightEar(int x, int y)
{
	gSoundDevice.earRight.x = x;
	gSoundDevice.earRight.y = y;
}

void SoundSetEars(int x, int y)
{
	SoundSetLeftEar(x, y);
	SoundSetRightEar(x, y);
}

void SoundPlayAt(sound_e sound, int x, int y)
{
	SoundPlayAtPlusDistance(sound, x, y, 0);
}

void SoundPlayAtPlusDistance(sound_e sound, int x, int y, int plusDistance)
{
	int distance, bearing;
	Vector2i origin = gSoundDevice.earLeft;
	Vector2i target;
	target.x = x;
	target.y = y;
	CalcChebyshevDistanceAndBearing(origin, target, &distance, &bearing);
	SoundPlayAtPosition(&gSoundDevice, sound, distance + plusDistance, bearing);
}

sound_e SoundGetHit(special_damage_e damage, int isActor)
{
	switch (damage)
	{
	case SPECIAL_FLAME:
		return SND_HIT_FIRE;
	case SPECIAL_POISON:
		return SND_HIT_GAS;
	case SPECIAL_PETRIFY:
		return SND_HIT_PETRIFY;
	case SPECIAL_CONFUSE:
		return SND_HIT_GAS;
	case SPECIAL_KNIFE:
		return isActor ? SND_KNIFE_FLESH : SND_KNIFE_HARD;
	case SPECIAL_EXPLOSION:
		return SND_HIT_GAS;
	default:
		return isActor ? SND_HIT_FLESH : SND_HIT_HARD;
	}
}
