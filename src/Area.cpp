#include "Area.h"
using namespace std;
using namespace godot;

void Area::_register_methods()
{
	register_method("_process", &Area::_process);
	register_property<Area, int>("sides", &Area::sides, 4); 

}

void Area::_init()
{
	sides = 4;
	top = true;
	bottom = true;
	left = true;
	right = true;
	//_displayInfo();
	areaTop = 0;
	areaBottom = 0;
	areaLeft = 0;
	areaRight = 0;
}

void Area::_process(float delta)
{

}

void  Area::setSides(int mySides, bool t, bool b, bool l, bool r)
{
	sides = mySides;
	top = t;
	bottom = b;
	left = l;
	right = r;
}

void Area::_print()
{
	cout << "sides: " << sides << " " << top << " " << bottom << " " << left << " " << right << " " << endl;
}

int Area::getSides()
{
	return sides;
}

bool Area::getAreaTop()
{
	return top;
}

bool Area::getAreaBottom()
{
	return bottom;
}

bool Area::getAreaLeft()
{
	return left;
}

bool Area::getAreaRight()
{
	return right;
}


void Area::setTopArea(int t)
{
	areaTop = t;
}

void Area::setBottomArea(int b)
{
	areaBottom = b;
}

void Area::setLeftArea(int l)
{
	areaLeft = l;
}

void Area::setRightArea(int r)
{
	areaRight = r;
}

int godot::Area::getTopArea()
{
	return areaTop;
}

int godot::Area::getBottomArea()
{
	return areaBottom;
}

int godot::Area::getLeftArea()
{
	return areaLeft;
}

int godot::Area::getRightArea()
{
	return areaRight;
}



void Area::_displayInfo()
{
	cout << "sides: " << sides << endl;
}
