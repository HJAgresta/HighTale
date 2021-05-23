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

	int YUpperBound = grid->YCount - 1;
	int XUpperBound = grid->XCount - 1;

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
			if (i == XUpperBound || *"C" == *dataArray[j][i + 1])
			{
				connectionCount++;
			}
			if (j == YUpperBound || *"C" == *dataArray[j + 1][i])
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
				bool onBottom = j == YUpperBound;
				bool onTop = j == 0;
				bool onLeftEdge = i == 0;
				bool onRightEdge = i == XUpperBound;

				bool leftFilled = onLeftEdge || *"C" == *dataArray[j][i - 1];
				bool rightFilled = onRightEdge || *"C" == *dataArray[j][i + 1];
				bool upFilled = onTop || *"C" == *dataArray[j - 1][i];
				bool downFilled = onBottom || *"C" == *dataArray[j + 1][i];
				bool downLeftFilled = onBottom || onLeftEdge || *"C" == *dataArray[j + 1][i - 1];
				bool downRightFilled = onBottom || onRightEdge || *"C" == *dataArray[j + 1][i + 1];
				bool upLeftFilled = onTop || onLeftEdge || *"C" == *dataArray[j - 1][i - 1];
				bool upRightFilled = onTop || onRightEdge || *"C" == *dataArray[j - 1][i + 1];

				if (!downLeftFilled &&
					downRightFilled &&
					upLeftFilled &&
					upRightFilled &&
					downFilled &&
					leftFilled &&
					upFilled &&
					rightFilled)
				{
					//bottom left empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIDL"]))->instance();
				}
				else if (downLeftFilled &&
					!downRightFilled &&
					upLeftFilled &&
					upRightFilled &&
					downFilled &&
					leftFilled &&
					upFilled &&
					rightFilled)
				{
					//bottom right empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIDR"]))->instance();
				}
				else if (downLeftFilled &&
					downRightFilled &&
					!upLeftFilled &&
					upRightFilled &&
					downFilled &&
					leftFilled &&
					upFilled &&
					rightFilled)
				{
					//upper left empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIUL"]))->instance();
				}
				else if (downLeftFilled &&
					downRightFilled &&
					upLeftFilled &&
					!upRightFilled &&
					downFilled &&
					leftFilled &&
					upFilled &&
					rightFilled)
				{
					//upper right empty
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIIUR"]))->instance();
				}
				else if (upFilled &&
					leftFilled &&
					!downFilled &&
					!rightFilled)
				{
					//corner connection to the left and up
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIBR"]))->instance();
				}
				else if (upFilled &&
					!leftFilled &&
					!downFilled &&
					rightFilled)
				{
					//corner connection to the up and right
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIBL"]))->instance();
				}
				else if (!upFilled &&
					!leftFilled &&
					downFilled &&
					rightFilled)
				{
					//corner connection to the down and right
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WITL"]))->instance();
				}
				else if (!upFilled &&
					downFilled &&
					leftFilled &&
					!rightFilled)
				{
					//corner connection to the left and down
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WITR"]))->instance();
				}
				else if (!upFilled)
				{
					//no connection on top
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIT"]))->instance();
				}
				else if (!downFilled)
				{
					//no connection on bottom
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIB"]))->instance();
				}
				else if (!leftFilled)
				{
					//no connection on left
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIL"]))->instance();
				}
				else if (!rightFilled)
				{
					//no connection on right
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WIR"]))->instance();
				}
				else
				{
					//entirely connected
					curItem = (Node2D*)((Ref<PackedScene>)(ObjectTypes["WM"]))->instance();
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