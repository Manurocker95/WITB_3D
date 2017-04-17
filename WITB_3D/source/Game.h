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
#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include "sfil.h"
#include "sftd.h"
#include "sf2d.h"

#include "font_ttf.h"
#include "Settings.h"

#include "sound.h"
#include "scene.h"
#include "Box.h"
#include "SceneManager.h"

#include <stdio.h>

#define MAXTAPS 1000000
#define TIMER 5

class GameScreen : public Scene
{

public:

	GameScreen(int _taps);		// Constructor
	void Start();				// Método que inicializa las variables de la escena
	void Draw();				// Método que se encarga de pintar las cosas de la escena
	void CheckInputs();			// Método que comprueba los inputs del juegador
	void Update();				// Método que actualiza la escena
	void ShowEnd();
	void ResetBG();
	void NewColorBG();
private:

	int m_taps;					// Número de Taps 
	int m_currentBG;
	int m_counter;
	bool m_ended;				// Si hemos acabado 
	float offset = 0;
	touchPosition touch;
	u32 held;
	sf2d_texture * m_bgTop,*m_bgBot;
	sound * m_bgm,* m_sfxTap;
	Box* m_player;
	sftd_font* font;
};

#endif