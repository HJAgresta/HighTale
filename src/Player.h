#pragma once

#include "Common.h"
#include <KinematicCollision2D.hpp>
#include <KinematicBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <Input.hpp>

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class Player : public KinematicBody2D
	{
		GODOT_CLASS(Player, KinematicBody2D)

	public:
		static void _register_methods();

		void _init();

		void _ready();

		void _physics_process(float delta);

		float speed;


	private:
		unique_ptr<Vector2> Velocity;

		bool moving;

		AnimatedSprite* anim;

		Input* input;
	};
}

