#pragma once

#include "Common.h"
#include "Attack.h"
#include <String.hpp>
#include <KinematicCollision2D.hpp>
#include <KinematicBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D)

	public:

		static void _register_methods();

		virtual void _init();

	protected:
		enum state { IDLE, ALERT, FOLLOW, CHARGE, ATTACK, COOLDOWN };

		float reactTime = 1.0f;

		Ref<PackedScene> ThisAttack;

		state curState;

		Vector2 Direction;

		KinematicBody2D* Player;

		Attack* curAttack;

		float stateTime;

		int AttackIterator;

		void FacePlayer();
	};
}