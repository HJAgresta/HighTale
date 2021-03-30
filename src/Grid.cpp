#include "Grid.h"

class GridNode;

Grid::Grid()
{

}


Grid::~Grid()
{

	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < CollumnCount; j++)
		{

			delete Indicies[i][j];
		}
		delete Indicies[i];
	}
	delete Indicies;
}

Grid::Grid(int rowCount, int collumnCount)
{
	RowCount = rowCount;

	CollumnCount = collumnCount;

	Indicies = new GridNode**[RowCount];

	for (int i = 0; i < RowCount; i++)
	{
		Indicies[i] = new GridNode*[CollumnCount]; // build rows
	}

	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < CollumnCount; j++)
		{

			Indicies[i][j] = new GridNode(i, j);

		}
	}

}


bool Grid::AssignNode(int row, int collumn, GridObject* callObject)
{
	GridNode* node = Indicies[row][collumn];

	if (node->Occupant == nullptr)
		return false;
	else
	{
		node->Occupant = callObject;
		callObject->AssignedNode = node;
		return true;
	}
}

