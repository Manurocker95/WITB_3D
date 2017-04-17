#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

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

#include <fstream>
#include <sstream>
#include <sys/unistd.h>
#include "SplashScreen.h"
#include "Game.h"

class SceneManager
{
public:

	enum SCENES { SPLASH, GAME };	// No necesitamos pantalla de título 

	static SceneManager* instance();

	void setActualScene(SCENES _scene);
	void Start();
	void Update();
	bool isOut();
	void exitGame();
	void ReadData();
	void SaveTapsAndExit(int _taps);

private:

	SceneManager() {};  // Private so that it can  not be called
	static SceneManager* Instance;

	int m_taps;
	bool m_out;
	Scene* m_actualScene;
};

#endif