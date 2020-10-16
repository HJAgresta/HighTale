#pragma once

#include "Common.h"
#include "ProjectileAttack.h"
#include <Array.hpp>
#include <String.hpp>
#include <KinematicCollision2D.hpp>
#include <KinematicBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <PackedScene.hpp>
#include <Input.hpp>
#include <RandomNumberGenerator.hpp>
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

		void _init();

		void _ready();

		void _physics_process(float delta);

		void _free();

	private:
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