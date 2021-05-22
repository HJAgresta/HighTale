#include "MovingSingleEnemy.h"

void MovingSingleEnemy::_register_methods()
{
	register_method("_physics_process", &MovingSingleEnemy::_physics_process);
	register_method("_ready", &MovingSingleEnemy::_ready);
	register_method("_init", &MovingSingleEnemy::_init);
	register_method("TakeHit", &MovingSingleEnemy::TakeHit);
	register_property<MovingSingleEnemy, float>("Health", &MovingSingleEnemy::Health, 100.0f);
	register_property<MovingSingleEnemy, float>("Speed", &MovingSingleEnemy::Speed, 100.0f);
	register_property<MovingSingleEnemy, float>("followUntil", &MovingSingleEnemy::followUntil, 60.0f);
	register_property<MovingSingleEnemy, float>("fleeUntil", &MovingSingleEnemy::fleeUntil, 30.0f);
	register_property<MovingSingleEnemy, Ref<PackedScene>>("ThisAttack", &MovingSingleEnemy::ThisAttack, Ref<PackedScene>());
	register_property<MovingSingleEnemy, float>("reactTime", &MovingSingleEnemy::reactTime, 1.0f);
}


void MovingSingleEnemy::_init()
{
	//set our defaults
	curState = FOLLOW;
	stateTime = 0.0f;
	AttackIterator = 0;
	Health = 100.0f;
	Speed = 100.0f;
	followUntil = 60.0f;
	fleeUntil = 30.0f;
}

bool MovingSingleEnemy::TakeHit(float damage, Attack* incoming)
{

	Health = Health - damage;

	incoming->destroy();

	if (Health <= 0)
		this->Destroy();

	return true;
}

void MovingSingleEnemy::_ready()
{
	followUntil = followUntil * followUntil;
	fleeUntil = fleeUntil * fleeUntil;

	//get a refrence to the player, we use it alot
	Player = (KinematicBody2D*)get_node("../Player");
	anim = (AnimatedSprite*)get_node("AnimatedSprite");
}

void MovingSingleEnemy::_physics_process(float delta)
{
	stateTime += delta;
	float distanceToPlayer;
	switch (curState)
	{

	case FOLLOW:

		FacePlayer();

		distanceToPlayer = Player->get_global_position().distance_squared_to(this->get_global_position());

		if (distanceToPlayer > followUntil)
		{
			KinematicCollision2D* collider = *move_and_collide((Direction * Speed * delta));
			/*
			//if the collider is a nullpointer we didnt hit anything
			if (collider != nullptr) {
				//if its a static object we can see this way
				if (collider->get_collider()->is_class("StaticBody2D"))
				{
					cout << "Hit Static Body" << endl;
				}
			}
			*/
		}
		else if(distanceToPlayer < fleeUntil)
		{
			KinematicCollision2D* collider = *move_and_collide((Direction * -Speed * delta));
			/*
			//if the collider is a nullpointer we didnt hit anything
			if (collider != nullptr) {
				//if its a static object we can see this way
			}*/
		}
		else
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
			anim->stop();
			anim->set_frame(1ULL);

			//we want to get these when they are initalized incase we destroy the object during the
			//attack phase
			chargeTime = (float)curAttack->get("chargeTime");
			attackTime = (float)curAttack->get("attackTime");
			cooldownTime = (float)curAttack->get("cooldownTime");
		}



		break;
	case IDLE:
		break;
	case ALERT:

		FacePlayer();
		anim->stop();
		anim->set_frame(0ULL);

		if (reactTime < stateTime)
		{

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
			curState = FOLLOW;
		}
		break;

	}
}