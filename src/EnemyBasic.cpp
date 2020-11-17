#include "EnemyBasic.h"

void EnemyBasic::_register_methods()
{
	register_method("_physics_process", &EnemyBasic::_physics_process);
	register_method("_ready", &EnemyBasic::_ready);
	register_method("_init", &EnemyBasic::_init);
	register_property<EnemyBasic, Ref<PackedScene>>("ThisAttack", &EnemyBasic::ThisAttack, Ref<PackedScene>());
	register_property<EnemyBasic, float>("reactTime", &EnemyBasic::reactTime, 1.0f);
}


void EnemyBasic::_init()
{
	curState = ALERT;
	stateTime = 0.0f;
	AttackIterator = 0;

}

void EnemyBasic::_ready()
{
	Player = (KinematicBody2D*)get_node("../Player");
}

void EnemyBasic::_physics_process(float delta)
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