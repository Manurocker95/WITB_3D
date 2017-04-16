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

#include "SceneManager.h"

SceneManager* SceneManager::Instance = NULL;

SceneManager* SceneManager::instance()
{
		if (!Instance)   
			Instance = new SceneManager;

		return Instance;
}

void SceneManager::Start()
{
	//MAX SCORE DATA
	ifstream myReadFile(DATA2_FILE);
	m_taps = 0;

	if (myReadFile.good())
	{
		myReadFile >> m_taps;
	}
	else
	{
		std::ofstream ofs;
		ofs.open(DATA2_FILE + '\n');
		ofs << m_taps;
		ofs.close();
	}

	m_out = false;
	m_actualScene = new SplashScreen();
}

void SceneManager::setActualScene(SCENES _scene)
{
	delete (m_actualScene);

	switch (_scene)
	{
	case SPLASH:
		m_actualScene = new SplashScreen();
		break;
	case GAME:
		m_actualScene = new GameScreen(m_taps);
		break;
	}
	
}

void SceneManager::Update()
{
	if (!m_actualScene)
	{
		return;
	}

	m_actualScene->CheckInputs();
	m_actualScene->Update();
	m_actualScene->Draw();
}

bool SceneManager::isOut()
{
	return m_out;
}

void SceneManager::exitGame()
{
	m_out = true;
}

void SceneManager::SaveTapsAndExit(int _taps)
{
	if (_taps >= 0)
	{
		std::ofstream ofs;
		ofs.open(DATA2_FILE);
		ofs << _taps;
		ofs.close();
	}

	exitGame();
}