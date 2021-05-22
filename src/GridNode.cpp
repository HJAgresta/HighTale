#include "GridNode.h"


GridNode::GridNode()
{

}

GridNode::GridNode(int xCount, int yCount)
{
	XCount = xCount;

	YCount = yCount;

	Center = Vector2(XCount * 16.0f + 8.0f, YCount * 16.0f + 8.0f);

}