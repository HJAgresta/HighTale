#include "LevelGen.h"

using namespace std;
using namespace godot;

void godot::LevelGen::_register_methods()
{
	register_property("numAreas", &LevelGen::numAreas, 10); //small = 5 med = 10 large = 15
	
}

void godot::LevelGen::_init()
{
	numAreas = 10;
	listArea[0].setSides(4, true, true, true, true);
	listArea[1].setSides(2, true, true, false, false);
	listArea[2].setSides(2,false,false,true,true);
	listArea[3].setSides(1, false, true, false, false);
	listArea[4].setSides(1, false, false, true, false);
	listArea[5].setSides(1, false, false, false, true);
	listArea[6].setSides(1, true, false, false, false);
	listArea[7].setSides(2, true, false, true, false);
	listArea[8].setSides(2, true, false, false, true);
	listArea[9].setSides(2, false, true, true, false);
	listArea[10].setSides(2, false, true, false, true);

	//start location
	curLocationX = 2;
	curLocationY = 2;

	_genLevel();
}

void godot::LevelGen::_switchArea()
{
}

void godot::LevelGen::_process(float delta)
{
}

void LevelGen::_genLevel() 
{
	levelMap[curLocationX][curLocationY] = selectRoom();
	selectingRooms(curLocationX, curLocationY);

}

void godot::LevelGen::selectingRooms(int x, int y)
{
	if (x - 1 >= 0 && levelMap[x - 1][y].getSides() == NULL && levelMap[x][y].getAreaTop()) {
		//cout << "top" << endl;
		setTopRoom(x - 1, y);
		selectingRooms(x - 1, y);
	}

	if (x + 1 < 5 && levelMap[x + 1][y].getSides() == NULL && levelMap[x][y].getAreaBottom()) {
		//cout << "bottom" << endl;
		setBottomRoom(x + 1, y);
		selectingRooms(x + 1, y);
	}

	if (y - 1 >= 0 && levelMap[x][y - 1].getSides() == NULL && levelMap[x][y].getAreaLeft()) {
		//cout << "left" << endl;
		setLeftRoom(x, y - 1);
		selectingRooms(x, y - 1);
	}

	if (y + 1 < 5 && levelMap[x][y + 1].getSides() == NULL && levelMap[x][y].getAreaRight()) {
		//cout << "right" << endl;
		setRightRoom(x, y + 1);
		selectingRooms(x, y + 1);
	}
}
void godot::LevelGen::setTopRoom(int x, int y)
{
	cout << "square: (" << x << ", " << y << ") " << endl;
	srand((unsigned)time(0));
	int num = rand() % 7 + 1;
	Area room;

	while (!listArea[num].getAreaBottom()) {
		room = listArea[num];
		num = rand() % 7 + 1;
	}

	//cout << "top area: " << num << endl;
	listArea[num]._print();
	//return listArea[num];
	levelMap[x][y] = listArea[num];
}

void godot::LevelGen::setBottomRoom(int x, int y)
{
	cout << "square: (" << x << ", " << y << ") " << endl;
	srand((unsigned)time(0));
	int num = rand() % 10;
	Area room;

	while (!listArea[num].getAreaTop()) {
		room = listArea[num];
		num = rand() % 10;
	}

	//cout << "bottom area: " << num << endl;
	listArea[num]._print();
	//return listArea[num];
	levelMap[x][y] = listArea[num];
}

void godot::LevelGen::setLeftRoom(int x, int y)
{
	cout << "square: (" << x << ", " << y << ") " << endl;
	srand((unsigned)time(0));
	int num = rand() % 10;
	Area room;

	while (!listArea[num].getAreaRight()) {
		room = listArea[num];
		num = rand() % 10;
	}

	//cout << "left area: " << num << endl;
	listArea[num]._print();
	//return listArea[num];
	levelMap[x][y] = listArea[num];
}

void godot::LevelGen::setRightRoom(int x, int y)
{
	cout << "square: (" << x << ", " << y << ") " << endl;
	srand((unsigned)time(0));
	int num = rand() % 10;
	Area room;

	while (!listArea[num].getAreaLeft()) {
		room = listArea[num];
		num = rand() % 10;
	}

	//cout << "right area: " << num << endl;
	listArea[num]._print();
	//return listArea[num];
	levelMap[x][y] = listArea[num];
}
Area godot::LevelGen::selectRoom()
{
	cout << "square: (" << curLocationX << ", " << curLocationY << ") " << endl;
	//getting the starting room for the player
	srand((unsigned)time(0));
	int roomStart = rand() % 10;

	startArea = listArea[roomStart];

	//cout << "starting area: " << roomStart << endl;
	listArea[roomStart]._print();

	return listArea[roomStart];
}

