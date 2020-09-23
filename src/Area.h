#pragma once
#include "Common.h"
#include <Input.hpp>

namespace godot {
	///<summary>
	///Centralizes control calls for easy editing
	///</summary>

	class Area : public Object {
		GODOT_CLASS(Area, Object);


	public:
		static void _register_methods();

		void _init();

		void _process(float delta);

		void setSides(int mySides, bool t, bool b, bool l, bool r);

		void _print();

		int getSides();

		bool getAreaTop();
		bool getAreaBottom();
		bool getAreaLeft();
		bool getAreaRight();

		void setTopArea(int t);
		void setBottomArea(int b);
		void setLeftArea(int l);
		void setRightArea(int r);

		int getTopArea();
		int getBottomArea();
		int getLeftArea();
		int getRightArea();
		
	private: 

		void _displayInfo();

		int  sides;

		bool top;
		bool bottom;
		bool left;
		bool right;

		int areaTop;
		int areaBottom;
		int areaLeft;
		int areaRight;

	};
}