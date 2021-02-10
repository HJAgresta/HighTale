#pragma once
#include "Common.h"
#include "Enemy.h"

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class MovingSingleEnemy : public Enemy
	{
		GODOT_CLASS(MovingSingleEnemy, Enemy)

	public:

		static void _register_methods();

		void _init();

		void _ready();

		void _physics_process(float delta);

		float Health;

		float Speed;

		float followUntil;

		float fleeUntil;

		bool TakeHit(float damage, Attack* incoming);


	};
}
