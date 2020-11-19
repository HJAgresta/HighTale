#pragma once
#include "Attack.h"
#include "Common.h"
namespace godot {

	///<summary>
	///The Basic Projectile Attack Object
	///</summary>
	class AttackProjectile : public Attack
	{
		GODOT_CLASS(AttackProjectile, Attack)

	public:
		static void _register_methods();

		void _init();

		void _ready();

		void destroy();

		float time;

		void _physics_process(float delta);
	};

}