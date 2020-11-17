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
	Direction = this->get_position().direction_to(Player->get_position());

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