#include "LevelManager.h"

void LevelManager::_register_methods()
{
	register_method("_init", &LevelManager::_init);
}


void LevelManager::_init()
{
	grid = Grid(16, 32);
}