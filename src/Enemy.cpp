#include "Enemy.h"

void Enemy::_register_methods()
{
	register_method("_init", &Enemy::_init);
}

void Enemy::_init()
{

}

bool Enemy::Destroy()
{
	if (!this->is_queued_for_deletion())
		this->queue_free();

	return true;
}

///<summary>
///sets animation and sets the direction vector twoards the player
///</summary>
void Enemy::FacePlayer()
{
	Target = Player->get_position();

	//gets the direction to the player
	Direction = this->get_position().direction_to(Target);

	//if the magnitiude of x is greater than y
	//they it is either to the right or left primarily
	// if its positive its on one direction or the other
	if (abs(Direction.x) > abs(Direction.y))
	{
		if (Direction.x > 0)
		{
			anim->play("right");
		}
		else
		{
			anim->play("left");
		}
	}
	else
	{
		if (Direction.y > 0)
		{
			anim->play("down");
		}
		else
		{
			anim->play("up");
		}
	}
}