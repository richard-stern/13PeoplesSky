#pragma once
#include "GameObject.h"

class Level : public GameObject
{
public:
	Level();
	~Level();
	void Draw(aie::Renderer2D* _render);
	void Update(float _delta_time);
	
};

