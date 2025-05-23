/*
 * Copyright (c) 2019 Anthony Beaucamp.
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

#include "unity.h"

#ifdef __APPLE2__
  #pragma code-name("LC")
#endif

#ifdef __ATARIXL__
  #pragma code-name("SHADOW_RAM")
#endif

#ifdef __NES__
  #pragma rodata-name("BANK0")
  #pragma code-name("BANK0")
#endif

unsigned char InitNetwork(void)
{
#if defined __HUB__
	if (InitHub()) 
		return NETWORK_OK;
	return ADAPTOR_ERR;

#elif defined __FUJINET__
	FujiInit();
	return NETWORK_OK;

#elif defined __ULTIMATE__
	uii_identify();
	if (uii_data[2])
		return NETWORK_OK;
	return ADAPTOR_ERR;
	
#elif defined __IP65__
	if (ip65_init(ETH_INIT_DEFAULT)) return ADAPTOR_ERR;
	if (dhcp_init()) return DHCP_ERR;
	return NETWORK_OK;
	
#else
	return ADAPTOR_ERR;
	
#endif
}
