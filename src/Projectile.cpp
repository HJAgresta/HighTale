#include "Projectile.h"

void Projectile::_register_methods()
{
	register_method("_init", &Projectile::_init);
	register_method("_ready", &Projectile::_ready);
	register_method("_physics_process", &Projectile::_physics_process);
	register_method("counter", &Projectile::counter);
	register_property<Projectile, float>("chargeTime", &Projectile::chargeTime, 1.0f);
	register_property<Projectile, float>("attackTime", &Projectile::attackTime, 1.0f);
	register_property<Projectile, float>("cooldownTime", &Projectile::cooldownTime, 1.0f);
	register_property<Projectile, float>("speed", &Projectile::speed, 100.0f);
	register_property<Projectile, float>("range", &Projectile::range, 100.0f);
	register_property<Projectile, float>("damage", &Projectile::damage, 30.0f);
	register_property<Projectile, Vector2>("Direction", &Projectile::Direction, Vector2(0,0));

}

void Projectile::destroy()
{
	this->queue_free();
}

void Projectile::_init()
{

}

void Projectile::_ready()
{
	time = 0.0f;
}

void Projectile::counter()
{
	this->set_collision_mask_bit(1ll, false);

	this->set_collision_layer_bit(1ll, false);

	this->set_collision_mask_bit(2ll, true);

	this->set_collision_layer_bit(2ll, true);

	time = 0.0f;

	set("Direction", ((Vector2)get("Direction")).rotated((real_t)Math_PI));

}

void Projectile::_physics_process(float delta)
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
		if (colliders[i].has_method("TakeHit"))
		{
			//convert the collider to a player and call take damage
			((BreakableObject*)colliders[i])->TakeHit(damage, this);
		}
		else
		{
			destroy();
		}

	}

}