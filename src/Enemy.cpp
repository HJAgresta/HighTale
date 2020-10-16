#include "Enemy.h"

void Enemy::_register_methods()
{
	register_method("_physics_process", &Enemy::_physics_process);
	register_method("_ready", &Enemy::_ready);
	register_method("_init", &Enemy::_init);
	register_method("_free", &Enemy::_free);
	register_property<Enemy, Ref<PackedScene>>("ThisAttack", &Enemy::ThisAttack, Ref<PackedScene>());
	register_property<Enemy, float>("reactTime", &Enemy::reactTime, 1.0f);
}

void Enemy::_free()
{
	ThisAttack.unref();
	if (!curAttack->is_queued_for_deletion())
		curAttack->queue_free();
	this->queue_free();
}


void Enemy::_init()
{
	curState = ALERT;
	stateTime = 0.0f;
	AttackIterator = 0;

}

void Enemy::_ready()
{
	Player = (KinematicBody2D*)get_node("../Player");
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

void Enemy::_physics_process(float delta)
{
	stateTime += delta;

	switch (curState)
	{

	case FOLLOW:
		break;
	case IDLE:
		break;
	case ALERT:

		FacePlayer();

		if (reactTime < stateTime)
		{
			stateTime = 0.0f;
			curState = CHARGE;

			Attack* newAttack = (Attack*)ThisAttack->instance();

			newAttack->set_position(this->get_position());

			String name = this->get_name() + newAttack->get_name() + Variant(AttackIterator);

			newAttack->set_name(name);

			AttackIterator = AttackIterator + 1;

			get_parent()->add_child(newAttack, true);

			curAttack = (Attack*)get_node(NodePath("../" + name));

			curAttack->set_visible(false);
			curAttack->set_process(false);
			curAttack->set_physics_process(false);

		}
		break;
	case CHARGE:
		if (1.0f < stateTime)
		{
			cout << (*curAttack).chargeTime << endl;
			curAttack->set_visible(true);
			curAttack->set_process(true);
			curAttack->set_physics_process(true);
			stateTime = 0.0f;
			curState = ATTACK;
		}
		break;
	case ATTACK:
		if (1.0f < stateTime)
		{
			stateTime = 0.0f;
			curState = COOLDOWN;
		}
		break;
	case COOLDOWN:
		if (1.0f < stateTime)
		{
			stateTime = 0.0f;
			curState = ALERT;
		}
		break;

	}
}