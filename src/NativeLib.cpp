#include "Common.h"
#include "Player.h"
#include "StationarySingleEnemy.h"
#include "MovingSingleEnemy.h"
#include "Projectile.h"
#include "LevelManager.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<Player>();
	godot::register_class<Projectile>();
	godot::register_class<StationarySingleEnemy>();
	godot::register_class<MovingSingleEnemy>();
	godot::register_class<LevelManager>();
}
