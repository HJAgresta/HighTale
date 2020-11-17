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
	//set our defaults
	curState = ALERT;
	stateTime = 0.0f;
	AttackIterator = 0;
}

void EnemyBasic::_ready()
{
	//get a refrence to the player, we use it alot
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

			//create an instance of our refrenced attack
			//this calls init
			Attack* newAttack = (Attack*)ThisAttack->instance();

			//create a name for the attack that iterates
			String name = this->get_name() + newAttack->get_name() + Variant(AttackIterator);

			//sets the name to our iterated name
			newAttack->set_name(name);

			//why not do a little extra bug protection
			if (AttackIterator < INT_MAX)
				AttackIterator = AttackIterator + 1;
			else
				AttackIterator = INT_MIN;

			//add the object to the actual scene, this calls ready()
			get_parent()->add_child(newAttack, true);

			//get refrence to object we just created
			curAttack = (Attack*)(get_node(NodePath("../" + name)));

			//essesntially sets object to inactive
			curAttack->set_visible(false);
			curAttack->set_process(false);
			curAttack->set_physics_process(false);

			//we want to get these when they are initalized incase we destroy the object during the
			//attack phase
			chargeTime = (float)curAttack->get("chargeTime");
			attackTime = (float)curAttack->get("attackTime");
			cooldownTime = (float)curAttack->get("cooldownTime");

		}
		break;
	case CHARGE:
		if (chargeTime < stateTime)
		{
			//set attack location to where we are
			curAttack->set_position(this->get_position());

			//activate object after charged
			curAttack->set_visible(true);
			curAttack->set_process(true);
			curAttack->set_physics_process(true);

			stateTime = 0.0f;
			curState = ATTACK;
		}
		break;
	case ATTACK:
		if (attackTime < stateTime)
		{
			stateTime = 0.0f;
			curState = COOLDOWN;
		}
		break;
	case COOLDOWN:
		if (cooldownTime < stateTime)
		{
			stateTime = 0.0f;
			curState = ALERT;
		}
		break;

	}
}