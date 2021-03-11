#include "GridNode.h"


GridNode::GridNode()
{

}

GridNode::GridNode(int row, int collumn)
{
	Collumn = collumn;

	Row = row;

	Center = Vector2(row * 16.0f + 8.0f, collumn * 16.0f + 8.0f);

}