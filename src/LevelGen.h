#pragma once
#include "Common.h"
#include "Area.h"
#include <Input.hpp>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  


namespace godot {
	///<summary>
	///Centralizes control calls for easy editing
	///</summary>

	class LevelGen : public Object {
		GODOT_CLASS(LevelGen, Object);

	public:
		static void _register_methods();

		void _init();

		void _switchArea();

		int numAreas;

		void _process(float delta);

		godot::Area startArea;

		godot::Array ListAreas;

		void _genLevel();

		Area a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11; 

		Area listArea[12] = { a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11 };

		int curLocationX;

		int curLocationY;

	private:
		void setTopRoom(int x, int y);

		void setBottomRoom(int x, int y);

		void setLeftRoom(int x, int y);

		void setRightRoom(int x, int y);

		void selectingRooms(int x, int y);

		Area selectRoom();

		Area baseArea;

		Area levelMap[5][5];

		
	};
}