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

#pragma once
#ifndef _SPLASH_SCREEN_H_
#define _SPLASH_SCREEN_H_

#include <sftd.h>
#include <sf2d.h>
#include <sfil.h>

#include "Settings.h"

#include "sound.h"
#include "scene.h"
#include "SceneManager.h"


class SplashScreen: public Scene
{

public:

	enum SPLASH_STATE { OPENING, STAY, ENDING };

	SplashScreen();						// Constructor
	~SplashScreen();
	
	void Start() override;				// Método que inicializa las variables de la escena
	void Draw() override;				// Método que se encarga de pintar las cosas de la escena
	void CheckInputs() override;		// Método que comprueba los inputs del juegador
	void Update() override;				// Método que actualiza la escena
	void GoToGame();
private:

	int m_splashOpacity, m_scTimer;
	bool m_sfxSplash, m_goToGame;
	sound * m_SFX;
	sf2d_texture * m_bgTop, *m_bgBot;
	SPLASH_STATE m_splashOpeningState;
};

#endif