#pragma once
#include "Collider.h"

class PrimRectangle : public Collider
{
public:

	PrimRectangle(int nWidth, int nHeight);

	~PrimRectangle();
};

class PrimTriangle : public Collider
{
public:

	PrimTriangle(Vector2 v2BotLeft, Vector2 v2Top, Vector2 v2BotRight);

	~PrimTriangle();
};



