#include "AttackProjectile.h"

void AttackProjectile::_register_methods()
{
	register_method("_init", &AttackProjectile::_init);
	register_method("_ready", &AttackProjectile::_ready);
	register_method("_physics_process", &AttackProjectile::_physics_process);
	register_property<AttackProjectile, float>("chargeTime", &AttackProjectile::chargeTime, 1.0f);
	register_property<AttackProjectile, float>("attackTime", &AttackProjectile::attackTime, 1.0f);
	register_property<AttackProjectile, float>("cooldownTime", &AttackProjectile::cooldownTime, 1.0f);
	register_property<AttackProjectile, float>("speed", &AttackProjectile::speed, 100.0f);
	register_property<AttackProjectile, float>("range", &AttackProjectile::range, 100.0f);
	register_property<AttackProjectile, int>("damage", &AttackProjectile::damage, 30);
	register_property<AttackProjectile, Vector2>("Direction", &AttackProjectile::Direction, Vector2(0,0));

}

void AttackProjectile::destroy()
{
	this->queue_free();
}

void AttackProjectile::_init()
{

}

void AttackProjectile::_ready()
{
	time = 0.0f;
}

void AttackProjectile::_physics_process(float delta)
{
	time += delta;
	if (time > attackTime)
		destroy();

	//move the projectile
	this->set_global_position(this->get_global_position() + (delta * speed * Direction));
	//look for thing collided with
	Array colliders = get_overlapping_bodies();
	for (int i = 0; i < colliders.size(); i++)
	{
		//the player has a method called takeHit
		if (colliders[i].has_method("takeHit"))
		{
			//convert the collider to a player and call take damage
			((Player*)colliders[i])->takeHit(damage);
			//destroy the attack
			destroy();
		}

	}



}