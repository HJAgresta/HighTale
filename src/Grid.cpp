#include "Grid.h"

class GridNode;

Grid::Grid()
{

}

Grid::Grid(int rowCount, int collumnCount)
{

	RowCount = rowCount;

	CollumnCount = collumnCount;

	indicies = map<String, unique_ptr<GridNode>>();

	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < CollumnCount; j++)
		{

			indicies.insert(pair<String, unique_ptr<GridNode>>(String(i) + String(',') + String(j), make_unique<GridNode>(GridNode(i, j))));
			
		}
	}
}

godot::GridNode* Grid::GetNode(int row, int collumn)
{
	return &(*indicies[String(row) + String(',') + String(collumn)]);
}

