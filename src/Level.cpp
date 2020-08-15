#include "Level.h"

void Level::_register_methods()
{
	register_method("_process", &Level::_process);
	register_property<Level, float>("amplitude", &Level::amplitude, 10.0);
	register_property<Level, float>("speed", &Level::set_speed, &Level::get_speed, 1.0);

	register_signal<Level>((char *)"position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

Level::Level() {
}

Level::~Level() {
	// add your cleanup here
}

void Level::_init()
{
	// initialize any variables here
	time_passed = 0.0f;
	time_emit = 0.0f;
	amplitude = 10.0f;
	speed = 1.0f;
}


void Level::_process(float delta)
{
	time_passed += delta;

	Vector2 new_position = Vector2(
		amplitude + (amplitude * sin(time_passed * 2.0)),
		amplitude + (amplitude * cos(time_passed * 1.5))
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0) {
		emit_signal("position_changed", this, new_position);

		time_emit = 0.0;
	}
}

void Level::set_speed(float p_speed) {
	speed = p_speed;
}

float Level::get_speed() {
	return speed;
}
