#include "Player.h"

bool Controls::left, Controls::right, Controls::down, Controls::up;

void Player::_register_methods()
{
	register_method("_physics_process", &Player::_physics_process);
	register_property("speed", &Player::speed, 100.0f);
}


void Player::_init()
{
	speed = 100.0f;

	Velocity = make_unique<Vector2>();
}

//key presses
//https://docs.godotengine.org/en/3.0/classes/class_@globalscope.html?highlight=%40GlobalScope
void Player::_physics_process(float delta)
{
	Vector2 currentPos = get_position();

	if (Controls::left)
		Velocity->x = Velocity->x - speed;

	if (Controls::right)
		Velocity->x = Velocity->x + speed;

	if (Controls::down)
		Velocity->y = Velocity->y + speed;

	if (Controls::up)
		Velocity->y = Velocity->y - speed;

	//set_position(currentPos + (*Velocity * delta));

	//Collider->call("move_and_collide", *Velocity * delta)

	KinematicCollision2D* abba = *move_and_collide((*Velocity * delta));

	if (abba != nullptr) {

		if (abba->get_collider()->is_class("StaticBody2D"))
		{
			cout << "Hit Static Body" << endl;
		}

	}

	Velocity->x = 0;
	Velocity->y = 0;
}