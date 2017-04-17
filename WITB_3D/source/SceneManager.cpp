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
	// We read data in 3ds/data/WITB/witb.sav
	m_out = false;
	ReadData();
}

void SceneManager::ReadData()
{	
	m_taps = 0;
	
	std::ifstream myReadFile(DATA_FILE);

	if (myReadFile)
	{
		myReadFile >> m_taps;
		m_actualScene = new SplashScreen();
	}
	else
	{
		std::ifstream myReadFile2(DATA_FILE2);

		if (myReadFile2)
		{
			myReadFile2 >> m_taps;
		}
		else
		{
			std::ofstream outfile(DATA_FILE);
			outfile << m_taps;
			outfile.close();

			std::ofstream outfile2(DATA_FILE2);
			outfile2 << m_taps;
			outfile2.close();

			
		}

		m_actualScene = new GameScreen(m_taps);
	}
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
		std::ofstream outfile(DATA_FILE);
		outfile << _taps;
		outfile.close();
	}

	exitGame();
}