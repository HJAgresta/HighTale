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
		{"O","O","O","O","O","","O","O","O","O","O","","","","","","","O","O","O","O","O","O","O","O","O","O","O","O","O","O", "O"},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","HS","","","","HF","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","","O","O","O","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","","O","O","O","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","O","O","O","O","","","","","","","","","O","O"},
		{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","O","O","O","O","","","","","","","P","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","O","O","O","O","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","O","O","O","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","O","O"},
		{"O","O","O","O","O","O","","","","","","","","","","","","","","","","","","","","","O","","","","O","O"},
	};

	int** groupedNodes = new int*[grid->XCount];

	for (int i = 0; i < grid->XCount; i++)
	{
		groupedNodes[i] = new int [grid->YCount]; // build rows
	}

	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			groupedNodes[i][j] = 0;
		}
	}


	//finds 1x1 rocks
	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			if (*dataArray[j][i] != *"O")
				continue;

			int connectionCount = 0;

			if (i != 0 && *"O" == *dataArray[j][i - 1])
				connectionCount++;

			if (j != 0 && *"O" == *dataArray[j - 1][i])
				connectionCount++;

			if (i != grid->XCount - 1 && *"O" == *dataArray[j][i + 1])
				connectionCount++;

			if (j != grid->YCount - 1 && *"O" == *dataArray[j + 1][i])
				connectionCount++;

			if (connectionCount < 2)
				groupedNodes[i][j] = 1;
				
		}
	}

	
	//sets obsticle types
	//0 - nothing
	//1 - 1x1
	//2 = 2x1
	//3 - 1x2
	//4 - 2x2
	//8 - edge
	//9 - cliff
	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			if (*dataArray[j][i] != *"O")
				continue;

			if (groupedNodes[i][j] != 0)
				continue;

			if (i == 0 || i == grid->XCount - 1
				|| j == 0 || j == grid->YCount - 1)
			{
				groupedNodes[i][j] = 8;
				continue;
			}

			bool right = false;
			if (*"O" == *dataArray[j][i + 1])
			{
				right = true;
			}

			bool down = false;
			if (*"O" == *dataArray[j - 1][i])
				down = true;

			bool left = false;
			if (*"O" == *dataArray[j][i - 1])
				left = true;

			bool up = false;
			if (*"O" == *dataArray[j + 1][i])
				up = true;

		}
	}
	// places objects
	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			const char* objectName = dataArray[j][i];

			Node2D* curItem;

			if (*objectName == *"O")
			{
				if (i == 0)
				{
					if (j == 0)
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIIIDR"])->instance();
					}
					else if (j == grid->YCount - 1)
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIIUR"])->instance();
					}
					else if (*"O" == *dataArray[j - 1][i] && *"O" == *dataArray[j + 1][i])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIR"])->instance();
					}
					else if (*"O" == *dataArray[j - 1][i])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIBR"])->instance();
					}
					else if (*"O" == *dataArray[j + 1][i])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WITR"])->instance();
					}
					else
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();
					}

				}
				else if (i == grid->XCount - 1)
				{
					if (j == 0)
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIIIDL"])->instance();
					}
					else if (j == grid->YCount - 1)
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIIUL"])->instance();
					}
					else if (*"O" == *dataArray[j - 1][i] && *"O" == *dataArray[j + 1][i])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIL"])->instance();
					}
					else if (*"O" == *dataArray[j - 1][i])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIBR"])->instance();
					}
					else if (*"O" == *dataArray[j + 1][i])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WITR"])->instance();
					}
					else
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();
					}

				}
				else if (j == 0)
				{
					if (*"O" == *dataArray[j][i-1] && *"O" == *dataArray[j][i+1])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIB"])->instance();
					}
					else if (*"O" == *dataArray[j][i - 1])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIBR"])->instance();
					}
					else if (*"O" == *dataArray[j][i + 1])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIBL"])->instance();
					}
					else
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();
					}
				}
				else if (j == grid->YCount - 1)
				{
					if (*"O" == *dataArray[j][i - 1] && *"O" == *dataArray[j][i + 1])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WIT"])->instance();
					}
					else if (*"O" == *dataArray[j][i - 1])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WITR"])->instance();
					}
					else if (*"O" == *dataArray[j][i + 1])
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["WITL"])->instance();
					}
					else
					{
						curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();
					}
				}
				else
				{
					curItem = (Node2D*)((Ref<PackedScene>)StaticObjectTypes["R1x1"])->instance();
				}

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

	//delete obsitcle helper grid
	for (int i = 0; i < grid->XCount; i++)
	{
		delete groupedNodes[i];
	}
	delete groupedNodes;
}



void LevelManager::_init()
{

}