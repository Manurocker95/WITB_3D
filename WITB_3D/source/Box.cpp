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

#include "Box.h"

Box::Box(int x, int y, sf2d_texture* sprite, bool multipleFrames, int numFrames, int sizePerFrame, int _taps)
{
	m_x = x;
	m_y = y;
	m_sprite = sprite;
	m_multipleFrames = multipleFrames;
	m_numFrames = numFrames;
	m_sizePerFrame = sizePerFrame;
	m_moving = false;
	m_currentFrame = 0;
	m_secondaryCounter = 0;

	if (_taps < FIRSTSTAGE)
	{
		m_yOffset = 0;
		m_state = CLOSED;
	}
	else if (_taps < SECONDSTAGE && _taps >= FIRSTSTAGE)
	{
		m_yOffset = 1;
		m_state = SEMIOPENED;
	}
	else if (_taps < THIRDSTAGE && _taps >= SECONDSTAGE)
	{
		m_yOffset = 2;
		m_state = SEMISEMIOPENED;
	}
	else if (_taps >= THIRDSTAGE && _taps < OPENEDTAP)
	{
		m_yOffset = 3;
		m_state = ALMOSTOPENED;
	}
	else
	{
		m_yOffset = 4;
		m_state = OPENED;
	}
}

void Box::Update(int _taps)
{
	if (m_moving)
	{
		m_secondaryCounter++;

		if (m_secondaryCounter > FRAMECOUNTER)
		{
			m_currentFrame++;
			m_secondaryCounter = 0;
		}

		if (m_currentFrame >= m_numFrames)
		{
			m_moving = false;
			m_currentFrame = 0;
		}
	}
	else
	{
		if (_taps == FIRSTSTAGE)
		{
			m_yOffset = 1;
			m_state = SEMIOPENED;
		}
		else if (_taps == SECONDSTAGE)
		{
			m_yOffset = 2;
			m_state = SEMISEMIOPENED;
		}
		else if (_taps == THIRDSTAGE)
		{
			m_yOffset = 3;
			m_state = ALMOSTOPENED;
		}
		else if (_taps == OPENEDTAP)
		{
			m_yOffset = 4;
			m_state = OPENED;
		}
	}
}

void Box::setYOffset(int value)
{
	m_yOffset = value;
	m_moving = false;
	m_currentFrame = 0;
	m_secondaryCounter = 0;

	if (m_yOffset == 0)
	{
		m_state = CLOSED;
	}
	else if (m_yOffset == 1)
	{
		m_state = SEMIOPENED;
	}
	else if (m_yOffset == 2)
	{
		m_state = SEMISEMIOPENED;
	}
	else if (m_yOffset == 3)
	{
		m_state = ALMOSTOPENED;
	}
	else
	{
		m_state = OPENED;
	}
}

void Box::Animate()
{
	m_moving = true;
	m_currentFrame = 0;
	m_secondaryCounter = 0;
}

void Box::Draw(float offset)
{
	if (m_multipleFrames)
	{
		sf2d_draw_texture_part(m_sprite, m_x - offset, m_y, m_currentFrame*m_sizePerFrame, m_yOffset*m_sizePerFrame, m_sizePerFrame, m_sizePerFrame);
	}
	else
	{
		sf2d_draw_texture(m_sprite, m_x, m_y);
	}
}

sf2d_texture* Box::getSprite()
{
	return m_sprite;
}

void Box::setSprite(sf2d_texture* sprite)
{
	m_sprite = sprite;
}

void Box::setX(int value)
{
	m_x = value;
}

int Box::getX()
{
	return m_x;
}

void Box::setY(int value)
{
	m_y = value;
}

int Box::getY()
{
	return m_y;
}


Box::GAME_STATES Box::getState()
{
	return m_state;
}

void Box::setState(Box::GAME_STATES value)
{
	m_state = value;
}


void Box::setNumFrames(int value)
{
	m_numFrames = value;
	m_currentFrame = 0;
}

int Box::getNumFrames()
{
	return m_numFrames;
}

void Box::setFrameSize(int value)
{
	m_sizePerFrame = value;
}

int Box::getFrameSize()
{
	return m_sizePerFrame;
}

bool Box::setMoving(bool value)
{
	m_moving = value;
}
