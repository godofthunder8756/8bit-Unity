/*
 * Copyright (c) 2021 Anthony Beaucamp.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented * you must not
 *   claim that you wrote the original software. If you use this software in a
 *   product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not
 *   be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any distribution.
 *
 *   4. The names of this software and/or it's copyright holders may not be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 */

#include "../../unity.h"
#include <stdarg.h>

// Workaround for missing text printing

void screensize(unsigned char *xSize, unsigned char *ySize) 
{
	*xSize = 40; *ySize = 17;
}

void gotoxy(unsigned char col, unsigned char row) 
{
	txtX = col; txtY = row;
}

int cprintf(const char* format, ...) 
{
	unsigned char buffer[40];
	va_list vl;
	
	va_start(vl, format);
	sprintf(buffer, format, vl);
	va_end(vl);
	
	if (txtX + strlen(buffer) > 39)
		buffer[39-txtX] = 0;
	PrintStr(buffer);
	txtX += strlen(buffer);
	if (txtX > 39) {
		txtX -= 40;
		txtY++;
	}
}

char *gets(char *s)
{
	// Reset buffer
	s[0] = 0;

	// Run input loop
	ShowKeyboardOverlay();
	while (1) {
		if (KeyboardOverlayHit() && InputStr(16, s, 16, GetKeyboardOverlay()))
			break;
		UpdateDisplay();
	}
	HideKeyboardOverlay();
}

int putchar (int c)
{
	PrintChr(c);
}
