#include "LevelManager.h"

void LevelManager::_register_methods()
{
	register_property("StaticObjectTypes", &LevelManager::ObjectTypes, Dictionary());
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
		{"C","C","C","C","C","","C","C","C","C","C","","","","","","","C","C","C","C","C","C","C","C","C","C","C","C","C","C", "C"},
		{"C","","","","","","","","","","C","","","","","","","","","","","","","","","","","C","C","C","C","C"},
		{"C","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","HS","","","","HF","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","","","","","","","2x1-R","2x1-R","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","","","","","","","","","","","","","","","","C","C","C","","","","","","","","","C","C"},
		{"C","","","","2x2-R","2x2-R","","","","1x2-R","","","","","","","","","","C","C","C","","","","","","","","","C","C"},
		{"C","","","","2x2-R","2x2-R","","","","1x2-R","","","","","","","C","C","C","C","C","C","","","","","","","","","C","C"},
		{"","","","","","","","","","","","","","","","","","","","","C","C","","","","","","","","","C","C"},
		{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","","C","C","","","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","C","C","C","C","","","","","","","P","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","C","C","C","C","","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","","","C","C","C","","","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","","C","C","","","","","","","","","","","","","","","","","","","","","","","","","","","C","C"},
		{"C","C","C","C","C","C","","","","","","","","","","","","","","","","","","","","","C","","","C","C","C"},
	};


	//finds 1x1 rocks
	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			if (*dataArray[j][i] != *"C")
				continue;

			int connectionCount = 0;

			if (i == 0 || *"C" == *dataArray[j][i - 1])
			{
				connectionCount++;
			}
			if (j == 0 || *"C" == *dataArray[j - 1][i])
			{
				connectionCount++;
			}
			if (i == grid->XCount - 1 || *"C" == *dataArray[j][i + 1])
			{
				connectionCount++;
			}
			if (j == grid->YCount - 1 || *"C" == *dataArray[j + 1][i])
			{
				connectionCount++;
			}
			if (connectionCount <= 1)
			{
				dataArray[j][i]  = "1x1-R";
			}
		}
	}

	// places objects
	for (int i = 0; i < grid->XCount; i++)
	{
		for (int j = 0; j < grid->YCount; j++)
		{
			String objectName = String(dataArray[j][i]);

			if (objectName == "")
				continue;

			Node2D* curItem = nullptr;

			Vector2 positionShift = Vector2();

			if (objectName.find("x") != -1)
			{
				PoolRealArray dimensions = objectName.substr(0, objectName.find("-")).split_floats("x");

				curItem = (Node2D*)((Ref<PackedScene>)ObjectTypes[objectName])->instance();

				for (int k = 0; k < dimensions[0]; k++)
				{
					for (int l = 0; l < dimensions[1]; l++)
					{
						dataArray[j + l][i + k] = "";

						grid->Indicies[i + k][j + l]->Occupant = curItem;

					}
				}


				positionShift = Vector2(dimensions[0] - 1, dimensions[1] - 1) * 16;


			}
			else if (objectName == "C")
			{

				if (j < grid->YCount - 1 &&
					i != 0 &&
					*"C" != *dataArray[j + 1][i - 1] &&
					*"C" == *dataArray[j + 1][i] &&
					*"C" == *dataArray[j][i - 1] &&
					(j == 0 ||
						*"C" == *dataArray[j - 1][i - 1] &&
						*"C" == *dataArray[j - 1][i] &&
						(i < grid->XCount - 1 ||
							*"C" == *dataArray[j][i + 1] &&
							*"C" == *dataArray[j - 1][i + 1]) &&
						(j == 0 || i < grid->XCount - 1 ||
							*"C" == *dataArray[j - 1][i + 1])))
				{
					//bottom left empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIDL"]))->instance();
				}
				else if (j < grid->YCount - 1 &&
					i != grid->XCount - 1 &&
					*"C" != *dataArray[j + 1][i + 1] &&
					*"C" == *dataArray[j + 1][i] &&
					*"C" == *dataArray[j][i + 1] &&
					(j == 0 ||
						*"C" == *dataArray[j - 1][i] &&
						*"C" == *dataArray[j - 1][i + 1]) &&
					(i == 0 ||
						*"C" == *dataArray[j][i - 1] &&
						*"C" == *dataArray[j - 1][i - 1]) &&
					(i == 0 || j == 0 ||
						*"C" == *dataArray[j - 1][i - 1]))
				{
					//bottom right empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIDR"]))->instance();
				}
				else if (j > 0 &&
					i < grid->XCount - 1 &&
					*"C" == *dataArray[j - 1][i] &&
					*"C" != *dataArray[j - 1][i + 1] &&
					*"C" == *dataArray[j][i + 1] && 
					(j == grid->YCount - 1 ||
						*"C" == *dataArray[j + 1][i + 1] &&
						*"C" == *dataArray[j + 1][i]) &&
					(i == 0 ||
						*"C" == *dataArray[j][i - 1] &&
						*"C" == *dataArray[j - 1][i - 1]) &&
					(i == 0 || j == grid->YCount - 1 ||
						*"C" == *dataArray[j + 1][i - 1]))
				{
					//upper right empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIUR"]))->instance();
				}
				else if (j > 0 &&
					i > 0 &&
					*"C" == *dataArray[j - 1][i] &&
					*"C" != *dataArray[j - 1][i - 1] &&
					*"C" == *dataArray[j][i - 1] &&
					(j == grid->YCount - 1 ||
						*"C" == *dataArray[j + 1][i - 1] &&
						*"C" == *dataArray[j + 1][i]) &&
					(i < grid->XCount - 1 ||
						*"C" == *dataArray[j][i + 1] &&
						*"C" == *dataArray[j - 1][i + 1]) &&
					(i < grid->XCount - 1 || j == grid->YCount - 1 ||
						*"C" == *dataArray[j + 1][i + 1]))
				{
					//upper left empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIUL"]))->instance();
				}
			}
			else if (objectName == "P")
			{
				player->set_position(grid->Indicies[i][j]->Center);

				continue;
			}
			else if (objectName != "")
			{
				curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes[objectName]))->instance();
			}
			else
			{
				continue;
			}

			if (curItem == nullptr)
				curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["1x1-R"]))->instance();

			//create a name for the object that iterates
			curItem->set_name(curItem->get_name() + String("-") + Variant(i) + String(",") + Variant(j));

			grid->Indicies[i][j]->Occupant = curItem;

			curItem->set_position(grid->Indicies[i][j]->Center + positionShift);

			add_child(curItem, true);
		}
	}

}



void LevelManager::_init()
{

}