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

#include "Game.h"

GameScreen::GameScreen(int _taps) : Scene ()
{
	m_taps = _taps;

	if (m_taps < MAXTAPS)
	{
		m_ended = false;
	}
	else
	{
		m_ended = true;
	}

	Start();
}

void GameScreen::Start()
{
	ndspChnWaveBufClear(1);
	ndspChnWaveBufClear(2);
	font = sftd_load_font_mem(font_ttf, font_ttf_size);
	m_player = new Box(TOP_WIDTH / 2 - 80, 60, sfil_load_PNG_file(IMG_BOX_SPRITE, SF2D_PLACE_RAM), true, 5, 150, m_taps);
	offset = 0;

	if (!m_ended)
	{
		m_bgTop = sfil_load_PNG_file(IMG_BG_GAME_TOP, SF2D_PLACE_RAM);
		m_bgBot = sfil_load_PNG_file(IMG_BG_GAME_BOT, SF2D_PLACE_RAM);
	}
	else
	{
		m_bgTop = sfil_load_PNG_file(IMG_BG_END_TOP, SF2D_PLACE_RAM);
		m_bgBot = sfil_load_PNG_file(IMG_BG_END_BOT, SF2D_PLACE_RAM);
	}

	m_bgm = new sound(SND_BGM_GAME, 1, true);
	m_sfxTap = new sound(SND_SFX_TAP, 2, false);
	m_bgm->play();
}

void GameScreen::Draw()
{
	
	// 3D effect
	//offset = CONFIG_3D_SLIDERSTATE * 20;

	if (!m_ended)
	{
		//Pantalla de arriba
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(m_bgTop, 0, 0);

		m_player->Draw(offset);

		sftd_draw_text(font, 15, 5, C_WHITE, TAPTEXTSIZE, "Taps:");
		sftd_draw_text(font,85, 5, C_WHITE, TAPTEXTSIZE, std::to_string(m_taps).c_str());

		sf2d_end_frame();

		//Pantalla de abajo
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(m_bgBot, 0, 0);
		sftd_draw_text(font, BOTTOM_WIDTH / 2 - 65, HEIGHT / 2 - 30, C_WHITE, MESSAGESIZE, "Tap here!");
		sf2d_end_frame();
	}
	else
	{
		//Pantalla de arriba
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(m_bgTop, 0, 0);

		sftd_draw_text(font, 120, 165, C_BLACK, TAPTEXTSIZE, "YOU GOT IT! ");
		sf2d_end_frame();

		//Pantalla de abajo
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture(m_bgBot, 0, 0);
		sftd_draw_text(font, 40, HEIGHT / 2 - 30-50, C_BLACK, MESSAGESIZE, "YOU ARE AWESOME!!");
		sftd_draw_text(font, 40, HEIGHT / 2 -20, C_RED, MESSAGESIZE, "TOUCH TO RESTART!");
		sf2d_end_frame();
	}
}

void GameScreen::Update()
{
	if (!m_ended)
	{
		if (m_currentBG == 0 && m_taps >= FIRSTSTAGE && m_taps < SECONDSTAGE)
		{
			m_currentBG = 1;
			NewColorBG();
		}
		else if (m_currentBG == 1 && m_taps >= SECONDSTAGE && m_taps < THIRDSTAGE)
		{
			m_currentBG = 2;
			NewColorBG();
		}
		else if (m_currentBG == 2 && m_taps >= THIRDSTAGE && m_taps < OPENEDTAP)
		{
			m_currentBG = 3;
			NewColorBG();
		}

		m_player->Update(m_taps);
	}
}

void GameScreen::CheckInputs()
{
	hidScanInput();

	//Salimos pulsando Select
	if ((hidKeysDown() & KEY_SELECT))
	{
		SceneManager::instance()->SaveTapsAndExit(m_taps);
	}

	if (hidKeysDown() & KEY_START)
	{
		std::ofstream outfile(DATA_FILE);
		outfile << m_taps;
		outfile.close();
	}

	if (DEBUGMODE)
	{
		if (hidKeysDown() & KEY_R)
		{
			ResetBG();
		}

		if (hidKeysDown() & KEY_L)
		{
			if (!m_ended)
			{
				m_taps+=FIRSTSTAGE;
				m_player->Animate();

				if (m_taps >= MAXTAPS)
				{
					ShowEnd();
				}
			}
		}
	}

	if (hidKeysDown() & KEY_TOUCH)
	{
		if (!m_ended)
		{
			m_taps++;
			m_player->Animate();

			if (m_taps >= MAXTAPS)
			{
				ShowEnd();
			}
		}
		else
		{
			ResetBG();
		}

		//m_sfxTap->play();
	}
}

void GameScreen::ShowEnd()
{
	sf2d_free_texture(m_bgTop);
	sf2d_free_texture(m_bgBot);

	m_bgTop = sfil_load_PNG_file(IMG_BG_END_TOP, SF2D_PLACE_RAM);
	m_bgBot = sfil_load_PNG_file(IMG_BG_END_BOT, SF2D_PLACE_RAM);

	m_ended = true;
}

void GameScreen::NewColorBG()
{
	sf2d_free_texture(m_bgTop);
	sf2d_free_texture(m_bgBot);

	switch (m_currentBG)
	{
	case 0:
		m_bgTop = sfil_load_PNG_file(IMG_BG_GAME_TOP, SF2D_PLACE_RAM);
		m_bgBot = sfil_load_PNG_file(IMG_BG_GAME_BOT, SF2D_PLACE_RAM);
		break;
	case 1:
		m_bgTop = sfil_load_PNG_file(IMG_BG_GAME_B_TOP, SF2D_PLACE_RAM);
		m_bgBot = sfil_load_PNG_file(IMG_BG_GAME_B_BOT, SF2D_PLACE_RAM);
		break;
	case 2:
		m_bgTop = sfil_load_PNG_file(IMG_BG_GAME_C_TOP, SF2D_PLACE_RAM);
		m_bgBot = sfil_load_PNG_file(IMG_BG_GAME_C_BOT, SF2D_PLACE_RAM);
		break;
	case 3:
		m_bgTop = sfil_load_PNG_file(IMG_BG_GAME_D_TOP, SF2D_PLACE_RAM);
		m_bgBot = sfil_load_PNG_file(IMG_BG_GAME_D_BOT, SF2D_PLACE_RAM);
		break;
	}

}

void GameScreen::ResetBG()
{
	m_taps = 0;
	m_player->setYOffset(0);

	sf2d_free_texture(m_bgTop);
	sf2d_free_texture(m_bgBot);

	m_bgTop = sfil_load_PNG_file(IMG_BG_GAME_TOP, SF2D_PLACE_RAM);
	m_bgBot = sfil_load_PNG_file(IMG_BG_GAME_BOT, SF2D_PLACE_RAM);
	m_ended = false;
}
