#pragma once

#include "Common.h"
#include "BreakableObject.h"
#include <Area2D.hpp>
#include <AnimatedSprite.hpp>
#include <KinematicBody2D.hpp>

namespace godot {
	///<summary>
	///The Basic Attack Object
	///</summary>
	class Attack : public Area2D
	{
		GODOT_CLASS(Attack, Area2D)

	public:

		static void _register_methods();

		virtual void _init();

		virtual void destroy();

		virtual void counter();

		float chargeTime = 1.0f;

		float attackTime = 1.0f;

		float cooldownTime = 1.0f;

		float speed = 100.0f;

		float range = 100.0f;

		float damage = 30.0f;

		Vector2 Direction = Vector2(0,0);

	protected:

		float stateTime = 0.0f;
	};
}