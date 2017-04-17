/* This file is part of What's in the Box 3DS!

Copyright (C) 2017 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/


#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <sys/stat.h>

#include "SceneManager.h"

ndspWaveBuf waveBuf;

int main()
{
	// Inicializamos los servicios
	// Srv
	srvInit();

	// SF2D + SFIL (Imágenes + gpu)
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0, 0, 0, 255));
	sf2d_set_3D(false);

	//Sftd (Textos)
	sftd_init();

	// Romfs
	romfsInit();

	// Sound - Necesita dumpear dsp de la consola
	ndspInit();

	//Creating Data
	mkdir("/3ds", 0777);
	mkdir("/3ds/data", 0777);
	mkdir("/3ds/data/WITB", 0777);

	SceneManager::instance()->Start();

	while (aptMainLoop())
	{
		// Update: Check inputs + Draw
		SceneManager::instance()->Update();

		if (SceneManager::instance()->isOut())
		{
			break;
		}

		sf2d_swapbuffers();
	}

	// Salimos de los servicios y eliminamos de memoria los obj. sobrantes
	romfsExit();
	ndspExit();
	sf2d_fini();
	sftd_fini();

	return 0;
}