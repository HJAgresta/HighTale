#include "LevelManager.h"

void LevelManager::_register_methods()
{
	register_property("EnemyTypes", &LevelManager::EnemyTypes, Dictionary());
	register_property("StaticObjectTypes", &LevelManager::StaticObjectTypes, Dictionary());
	register_method("_init", &LevelManager::_init);
	register_method("_ready", &LevelManager::_ready);
}

void LevelManager::_ready()
{

	const char* dataArray[32][16] = {
		{ "O","O","O","O","O","O","O","","","O","O","O","O","O","O","O" },
		{ "O","","","O","O","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","O","O","","","","","","","","","","","","O" },
		{ "O","","O","O","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","O","O","O","","","O" },
		{ "O","","","","","","","","","","O","O","O","","","O" },
		{ "O","","","","","","","","","","O","O","O","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","O","O","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","O","","","","","O","O","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","","O","","","","","","","","","","","","","O" },
		{ "O","","O","","","","","","","","","","","","","O" },
		{ "O","","","","","","","","","","","","","","","O" },
		{ "O","O","O","O","O","O","O","O","O","O","O","O","O","O","O","O" },
	};

	//create an instance of our refrenced attack
	//this calls init



	for (int i = 0; i < grid.RowCount; i++)
	{
		for (int j = 0; j < grid.CollumnCount; j++)
		{
			const char* objectName = dataArray[j][i];

			Node2D* curItem;

			if (*objectName == *"O")
			{
				curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();

			}
			else if (*objectName != *"")
			{
				curItem = (Node2D*)((Ref<PackedScene>)(EnemyTypes[String(objectName)]))->instance();
			}
			else
			{
				continue;
			}


			//create a name for the attack that iterates
			String name = curItem->get_name() + Variant(String(i) + String(",") + String(j));

			//sets the name to our iterated name
			curItem->set_name(name);

			WARN_PRINT(name);

			grid.Indicies[i][j]->Occupant = curItem;

			WARN_PRINT("placed");

			WARN_PRINT(grid.Indicies[0][0]->Center);

			curItem->set_position(grid.Indicies[i][j]->Center);

			WARN_PRINT("position set");

			add_child(curItem, true);

			WARN_PRINT("added");

		}
	}
}



void LevelManager::_init()
{


	/*
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 16; j++)
		{

			if (dataArray[i][j] == "O")
				1 + 1 + 1;

		}


	}*/
	grid = Grid(16, 32);
}