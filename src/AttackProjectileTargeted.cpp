#include "AttackProjectileTargeted.h"

void AttackProjectileTargeted::_register_methods()
{
	register_method("_init", &AttackProjectileTargeted::_init);
	register_method("_ready", &AttackProjectileTargeted::_ready);
	register_method("_physics_process", &AttackProjectileTargeted::_physics_process);
	register_property<AttackProjectileTargeted, float>("chargeTime", &AttackProjectileTargeted::chargeTime, 1.0f);
	register_property<AttackProjectileTargeted, float>("attackTime", &AttackProjectileTargeted::attackTime, 1.0f);
	register_property<AttackProjectileTargeted, float>("cooldownTime", &AttackProjectileTargeted::cooldownTime, 1.0f);
	register_property<AttackProjectileTargeted, float>("speed", &AttackProjectileTargeted::speed, 100.0f);
	register_property<AttackProjectileTargeted, float>("range", &AttackProjectileTargeted::range, 100.0f);
	register_property<AttackProjectileTargeted, int>("damage", &AttackProjectileTargeted::damage, 30);

}

void AttackProjectileTargeted::destroy()
{
	this->queue_free();
}

void AttackProjectileTargeted::_init()
{

}

void AttackProjectileTargeted::_ready()
{
	time = 0.0f;
	Direction = this->get_position().direction_to(((KinematicBody2D*)get_node("../Player"))->get_position());
}

void AttackProjectileTargeted::_physics_process(float delta)
{
	time += delta;
	if (time > attackTime)
		destroy();



	this->set_position(this->get_position() + (delta * speed * Direction));
	this->set_collision_layer(2);
	Array colliders = get_overlapping_bodies();
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i].has_method("takeHit"))
		{
			((Player*)colliders[i])->takeHit(damage);
			destroy();
		}

	}



}