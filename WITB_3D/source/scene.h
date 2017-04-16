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

#include "Filepaths.h"						// Incluimos en escena los filepaths para que sus hijos lo hereden

class Scene
{

protected:

public:
	Scene() {};													// Constructor
	~Scene() { };				// Destructor
	virtual void Start() {};				// Método que inicializa las variables de la escena
	virtual void Draw() {};					// Método que se encarga de pintar las cosas de la escena
	virtual void CheckInputs() {};			// Método que comprueba los inputs del juegador
	virtual void Update() {};				// Método que actualiza la escena
};
