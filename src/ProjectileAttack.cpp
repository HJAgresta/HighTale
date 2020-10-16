#include "ProjectileAttack.h"

void ProjectileAttack::_register_methods()
{
	register_method("_init", &ProjectileAttack::_init);
	register_method("_ready", &ProjectileAttack::_ready);
	register_method("_physics_process", &ProjectileAttack::_physics_process);
	register_property<ProjectileAttack, float>("chargeTime", &ProjectileAttack::chargeTime, 1.0f);
	register_property<ProjectileAttack, float>("attackTime", &ProjectileAttack::attackTime, 1.0f);
	register_property<ProjectileAttack, float>("cooldownTime", &ProjectileAttack::cooldownTime, 1.0f);
	register_property<ProjectileAttack, float>("speed", &ProjectileAttack::speed, 100.0f);
	register_property<ProjectileAttack, float>("range", &ProjectileAttack::range, 100.0f);
	register_property<ProjectileAttack, int>("damage", &ProjectileAttack::damage, 30);

}

void ProjectileAttack::_init()
{

}

void ProjectileAttack::_ready()
{
	Direction = this->get_position().direction_to(((KinematicBody2D*)get_node("../Player"))->get_position());
}

void ProjectileAttack::_physics_process(float delta)
{
	this->set_position(this->get_position() + (delta * speed * Direction));
	this->set_collision_layer(2);
	Array colliders = get_overlapping_bodies();
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i].has_method("takeHit"))
		{
			((Player*)colliders[i])->takeHit(damage);
		}

	}
}