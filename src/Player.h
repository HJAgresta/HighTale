#pragma once

#include "Common.h"
#include "BreakableObject.h"
#include <AnimatedSprite.hpp>
#include <Input.hpp>

namespace godot {

	class Attack;

	///<summary>
	///The main player object
	///</summary>
	class Player : public BreakableObject
	{
		GODOT_SUBCLASS(Player, BreakableObject)

	public:

		static void _register_methods();

		void _init();

		void _ready();

		bool TakeHit(float damage, Attack* incoming);

		void _physics_process(float delta);

		float speed;

	private:
		enum state { COUNTER, COOLDOWN, DEFAULT, PAUSE };

		state PlayerState = DEFAULT;

		unique_ptr<Vector2> Velocity;

		bool moving;

		AnimatedSprite* anim;

		Input* input;

		float counterTime;

		float counterCooldown;

		float stateTimer;
	};
}

