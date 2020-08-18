#pragma once

#include "Common.h"
#include <Input.hpp>
#include <Object.hpp>

namespace godot {
	///<summary>
	///Centralizes control calls for easy editing
	///</summary>
	class Controls : public Object
	{
		GODOT_CLASS(Controls, Object)

	public:
		static void _register_methods();

		void _init();

		void _process(float delta);

		static bool left, right, down, up;

	private:

		Input* input;
	};
}
