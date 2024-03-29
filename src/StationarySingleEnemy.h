#pragma once

#include "Common.h"
#include "Enemy.h"

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class StationarySingleEnemy : public Enemy
	{
		GODOT_SUBCLASS(StationarySingleEnemy, Enemy)

	public:

		static void _register_methods();

		void _init();

		void _ready();

		void _physics_process(float delta);

		float Health;

		bool TakeHit(float damage, Attack* incoming);
	};
}