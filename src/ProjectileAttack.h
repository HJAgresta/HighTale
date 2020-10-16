#pragma once
#include "Attack.h"
#include "Common.h"
namespace godot {

	///<summary>
	///The Basic Projectile Attack Object
	///</summary>
	class ProjectileAttack : public Attack
	{
		GODOT_CLASS(ProjectileAttack, Attack)

	public:
		static void _register_methods();

		void _init();

		void _ready();

		void _physics_process(float delta);

		Vector2 Direction;
	};

}