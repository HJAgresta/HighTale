#include "Grid.h"

class GridNode;

Grid::Grid()
{

}


Grid::~Grid()
{
	cout << "kill grid" << endl;
	for (int i = 0; i < XCount; i++)
	{
		for (int j = 0; j < YCount; j++)
		{

			delete Indicies[i][j];
		}
		delete Indicies[i];
	}
	delete Indicies;
}

Grid::Grid(int xCount, int yCount)
{
	XCount = xCount;

	YCount = yCount;

	Indicies = new GridNode**[XCount];

	for (int i = 0; i < XCount; i++)
	{
		Indicies[i] = new GridNode*[YCount]; // build rows
	}

	for (int i = 0; i < XCount; i++)
	{
		for (int j = 0; j < YCount; j++)
		{
			Indicies[i][j] = new GridNode(i, j);
		}
	}

}


bool Grid::AssignNode(int x, int y, GridObject* callObject)
{
	GridNode* node = Indicies[x][y];

	if (node->Occupant == nullptr)
		return false;
	else
	{
		node->Occupant = callObject;
		callObject->AssignedNode = node;
		return true;
	}
}

