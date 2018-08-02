#pragma once
#include "GameObject.h"
class Star : public GameObject
{
public:
	Star();
	~Star();

	void Draw(aie::Renderer2D* pRenderer);		//draws the star
};

