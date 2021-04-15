#include "LevelManager.h"

void LevelManager::_register_methods()
{
	register_property("EnemyTypes", &LevelManager::EnemyTypes, Dictionary());
	register_property("StaticObjectTypes", &LevelManager::StaticObjectTypes, Dictionary());
	register_method("_init", &LevelManager::_init);
	register_method("_ready", &LevelManager::_ready);
}


LevelManager::~LevelManager()
{

}

void LevelManager::_ready()
{
	player = (Player*)get_node("Player");

	grid = new Grid(32, 16);

	const char* dataArray[16][32] = {
		{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","", ""},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","HS","","","","HF","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","","O","O","O","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","","O","O","O","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","O","O","O","O","","","","","","","","","O",""},
		{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","O","O","O","O","","","","","","","P","","","","","","","","","","","","","","","","O",""},
		{"O","","","","O","O","O","O","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","O","O","O","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
		{"O","O","O","O","O","O","","","","","","","","","","","","","","","","","","","","","","","","","O",""},
	};


	//create an instance of our refrenced attack
	//this calls init
	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			const char* objectName = dataArray[j][i];

			Node2D* curItem;

			if (*objectName == *"O")
			{
				curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();

			}
			else if (*objectName == *"P")
			{
				player->set_position(grid->Indicies[i][j]->Center);

				continue;
			}
			else if (*objectName != *"")
			{
				curItem = (Node2D*)((Ref<PackedScene>)(EnemyTypes[String(objectName)]))->instance();
			}
			else
			{
				continue;
			}

			//create a name for the object that iterates
			curItem->set_name(curItem->get_name() + String("-") + Variant(i) + String(",") + Variant(j));

			grid->Indicies[i][j]->Occupant = curItem;

			curItem->set_position(grid->Indicies[i][j]->Center);

			add_child(curItem, true);
		}
	}
}



void LevelManager::_init()
{

}