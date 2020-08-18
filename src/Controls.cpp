#include "Controls.h"


void Controls::_init()
{
	left = false;
	right = false;
	down = false;
	up = false;

	input = Input::get_singleton();
}

//key presses
//https://docs.godotengine.org/en/3.0/classes/class_@globalscope.html?highlight=%40GlobalScope
void Controls::_process(float delta)
{
	left = input->is_key_pressed(65ll);
	right = input->is_key_pressed(68ll);
	down = input->is_key_pressed(83ll);
	up = input->is_key_pressed(87ll);

}

void Controls::_register_methods()
{
	register_method("_process", &Controls::_process);
	register_property<Controls, bool>("left", &Controls::left, false);
	register_property<Controls, bool>("right", &Controls::right, false);
	register_property<Controls, bool>("down", &Controls::down, false);
	register_property<Controls, bool>("up", &Controls::up, false);
}
