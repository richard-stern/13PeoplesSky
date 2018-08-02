#include "Primitives.h"
#include "Vector2.h"

// Rectangle
PrimRectangle::PrimRectangle(int nWidth, int nHeight) 
{
	float nHalfWidth = (float)(nWidth / 2);
	float nHalfHeight = (float)(nHeight / 2);

	// Add appropriate nodes...
	m_nodes->push_back(new ColliderNode(Vector2(-nHalfWidth, nHalfHeight), 1));
	m_nodes->push_back(new ColliderNode(Vector2(nHalfWidth, nHalfHeight), 2));
	m_nodes->push_back(new ColliderNode(Vector2(nHalfWidth, -nHalfHeight), 3));
	m_nodes->push_back(new ColliderNode(Vector2(-nHalfWidth, -nHalfHeight), 0));
}

PrimRectangle::~PrimRectangle() 
{

}

// Triangle

PrimTriangle::PrimTriangle(Vector2 v2BotLeft, Vector2 v2Top, Vector2 v2BotRight)
{
	// Add appropriate nodes...
	m_nodes->push_back(new ColliderNode(v2Top, 1));
	m_nodes->push_back(new ColliderNode(v2BotRight, 2));
	m_nodes->push_back(new ColliderNode(v2BotLeft, 0));
}

PrimTriangle::~PrimTriangle() 
{

}
