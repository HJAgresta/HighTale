#pragma once

#include "Common.h"
#include "Attack.h"
#include <String.hpp>
#include <KinematicCollision2D.hpp>
#include <KinematicBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <AnimatedSprite.hpp>

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class Enemy : public BreakableObject
	{
		GODOT_CLASS(Enemy, BreakableObject)

	public:

		static void _register_methods();

		virtual void _init();

	protected:
		enum state { IDLE, ALERT, FOLLOW, CHARGE, ATTACK, COOLDOWN };

		float reactTime = 1.0f;

		float chargeTime = 1.0f;

		float attackTime = 1.0f;

		float cooldownTime = 1.0f;

		Ref<PackedScene> ThisAttack;

		state curState;

		Vector2 Direction;

		KinematicBody2D* Player;

		Vector2 Target;

		Attack* curAttack;

		float stateTime;

		int AttackIterator;

		void FacePlayer();

		bool Destroy();

		AnimatedSprite* anim;
	};
}