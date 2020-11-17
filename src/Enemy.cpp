#include "Enemy.h"

void Enemy::_register_methods()
{
	register_method("_init", &Enemy::_init);
}

void Enemy::_init()
{

}

void Enemy::FacePlayer()
{
	//gets the direction to the player
	Direction = this->get_position().direction_to(Player->get_position());

	//if the magnitiude of x is greater than y
	//they it is either to the right or left primarily
	// if its positive its on one direction or the other
	if (abs(Direction.x) > abs(Direction.y))
	{
		if (Direction.x > 0)
		{
			this->set_rotation_degrees(90);
		}
		else
		{
			this->set_rotation_degrees(-90);
		}
	}
	else
	{
		if (Direction.y > 0)
		{
			this->set_rotation_degrees(180);
		}
		else
		{
			this->set_rotation_degrees(0);
		}
	}
}