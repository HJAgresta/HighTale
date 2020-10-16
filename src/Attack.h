#pragma once

#include "Common.h"
#include "Player.h"
#include "Attack.h"
#include <list>
#include <Area2D.hpp>
#include <AnimatedSprite.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>

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

		float chargeTime = 1.0f;

		float attackTime = 1.0f;

		float cooldownTime = 1.0f;

		float speed = 100.0f;

		float range = 100.0f;

		int damage = 30;

	protected:

		float stateTime = 0.0f;

	};
}