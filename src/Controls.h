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

		bool left, right, down, up;

		void _process(float delta);

	private:

		Input* input;
	};
}
