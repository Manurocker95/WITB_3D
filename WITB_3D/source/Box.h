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

#include "sftd.h"
#include "sfil.h"
#include "sf2d.h"
#include "Filepaths.h"

#define FIRSTSTAGE 100000
#define SECONDSTAGE 500000
#define THIRDSTAGE 900000
#define OPENEDTAP 1000000
#define FRAMECOUNTER 5

class Box 
{
public:
	enum GAME_STATES { CLOSED, SEMIOPENED, SEMISEMIOPENED, ALMOSTOPENED, OPENED, NONE };
	Box (int x, int y, sf2d_texture* sprite, bool multipleFrames, int numFrames, int sizePerFrame, int _taps);
	
	void Draw(float offset);
	void Update(int taps);

	void Animate();

	int getX();
	void setX(int value);
	int getY();
	void setY(int value);
	sf2d_texture* getSprite();
	void setSprite(sf2d_texture* sprite);
	void setNumFrames(int value);
	int getNumFrames();
	void setFrameSize(int value);
	int getFrameSize();
	Box::GAME_STATES getState();
	void setState(Box::GAME_STATES value);
	bool setMoving(bool value);
	void setYOffset(int value);
private:

	GAME_STATES m_state;
	sf2d_texture* m_sprite;
	int m_x;
	int m_y;
	int m_numFrames;
	int m_sizePerFrame;
	int m_currentFrame;
	int m_secondaryCounter;
	int m_yOffset;
	bool m_multipleFrames;
	bool m_moving;
};