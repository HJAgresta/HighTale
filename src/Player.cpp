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
	anim = (AnimatedSprite*)get_node("AnimatedSprite");
	moving = false;


	if (Controls::left && !Controls::right)
	{
		Velocity->x = Velocity->x - speed;
		if (!Controls::up && !Controls::down)
			anim->play("left");
		moving = true;
	}
	else if (Controls::right)
	{
		Velocity->x = Velocity->x + speed;
		if (!Controls::up && !Controls::down)
			anim->play("right");
		moving = true;
	}

	if (Controls::down && !Controls::up)
	{
		Velocity->y = Velocity->y + speed;
		anim->play("front");
		moving = true;
	}
	else if (Controls::up)
	{
		Velocity->y = Velocity->y - speed;
		anim->play("back");
		moving = true;
	}

	if (!moving)
		anim->stop();

	KinematicCollision2D* collider = *move_and_collide((*Velocity * delta));

	if (collider != nullptr) {

		if (collider->get_collider()->is_class("StaticBody2D"))
		{
			cout << "Hit Static Body" << endl;
		}

	}

	Velocity->x = 0;
	Velocity->y = 0;


}