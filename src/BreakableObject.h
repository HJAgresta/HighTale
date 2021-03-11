#pragma once

#include "Common.h"
#include "Attack.h"
#include "GridObject.h"
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>

namespace godot {

	class Attack;

	class BreakableObject : public GridObject 
	{
		GODOT_CLASS(BreakableObject, GridObject)

	public:
		static void _register_methods();

		virtual void _init();

		virtual bool TakeHit(float damage, Attack* incoming) { return false; }

		virtual bool Destroy() { return false; }

		float Health;

	};
};

