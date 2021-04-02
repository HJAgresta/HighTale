#pragma once
#include "Attack.h"
#include "Common.h"
namespace godot {

	///<summary>
	///The Basic Projectile Attack Object
	///</summary>
	class Projectile : public Attack
	{
		GODOT_SUBCLASS(Projectile, Attack)

	public:
		static void _register_methods();

		void _init();

		void _ready();

		void destroy();

		void counter();

		float time;

		void _physics_process(float delta);
	};

}