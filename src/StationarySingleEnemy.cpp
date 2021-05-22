#include "StationarySingleEnemy.h"

void StationarySingleEnemy::_register_methods()
{
	register_method("_physics_process", &StationarySingleEnemy::_physics_process);
	register_method("_ready", &StationarySingleEnemy::_ready);
	register_method("_init", &StationarySingleEnemy::_init);
	register_method("TakeHit", &StationarySingleEnemy::TakeHit);
	register_property<StationarySingleEnemy, float>("Health", &StationarySingleEnemy::Health, 100.0f);
	register_property<StationarySingleEnemy, Ref<PackedScene>>("ThisAttack", &StationarySingleEnemy::ThisAttack, Ref<PackedScene>());
	register_property<StationarySingleEnemy, float>("reactTime", &StationarySingleEnemy::reactTime, 1.0f);
}


void StationarySingleEnemy::_init()
{
	//set our defaults
	curState = ALERT;
	stateTime = 0.0f;
	AttackIterator = 0;
	Health = 100.0f;
}

bool StationarySingleEnemy::TakeHit(float damage, Attack* incoming)
{

	Health = Health - damage;

	incoming->destroy();

	if (Health <= 0)
		this->Destroy();

	return true;
}

void StationarySingleEnemy::_ready()
{
	//get a refrence to the player, we use it alot
	Player = (KinematicBody2D*)get_node("../Player");
	anim = (AnimatedSprite*)get_node("AnimatedSprite");
}

void StationarySingleEnemy::_physics_process(float delta)
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
		anim->stop();
		anim->set_frame(0ULL);

		if (reactTime < stateTime)
		{
			stateTime = 0.0f;
			curState = CHARGE;

			//create an instance of our refrenced attack
			//this calls init
			curAttack = (Attack*)ThisAttack->instance();

			//create a name for the attack that iterates
			String name = this->get_name() + curAttack->get_name() + Variant(AttackIterator);

			//sets the name to our iterated name
			curAttack->set_name(name);

			//why not do a little extra bug protection
			if (AttackIterator < INT_MAX)
				AttackIterator = AttackIterator + 1;
			else
				AttackIterator = INT_MIN;

			//add the object to the actual scene, this calls ready()
			get_parent()->add_child(curAttack, true);

			//essesntially sets object to inactive
			curAttack->set_visible(false);
			curAttack->set_process(false);
			curAttack->set_physics_process(false);

			//set animation
			anim->set_frame(1ULL);

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
			curAttack->set_global_position(this->get_global_position());

			//set the direction of the projectile
			curAttack->set("Direction", Variant(curAttack->get_global_position().direction_to(Player->get_global_position())));

			//Face the player when we throw it
			FacePlayer();
			anim->stop();
			//set animation
			anim->set_frame(0ULL);

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