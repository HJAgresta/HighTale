#include "Grid.h"

class GridNode;

void Grid::_register_methods()
{
	register_method("_init", &Grid::_init);
}


void Grid::_init()
{
}

Grid::Grid()
{
}

Grid::Grid(int collumnCount, int rowCount)
{

	CollumnCount = collumnCount;

	RowCount = rowCount;

	indicies = map<String, unique_ptr<GridNode>>();

	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < CollumnCount; j++)
		{

			indicies.insert(pair<String, unique_ptr<GridNode>>(String(i) + ',' + String(j), make_unique<GridNode>(GridNode(i, j))));
			
			WARN_PRINT(indicies[String(i) + ',' + String(j)]->Center);

		}
	}
}

