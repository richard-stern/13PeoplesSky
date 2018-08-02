#pragma once

#include <list>

#include <Renderer2D.h>

#include "Vector2.h"
#include "Matrix3.h"

#define WRAP_OFFSET 40.f

struct CollisionData;

class GameObject
{
protected:
	GameObject* m_pParent;
	std::list<GameObject*> m_Children;


	aie::Texture* m_pTexture;
	//DEFAULT: White
	//Hex value for the color
	unsigned int m_iColor;

	Vector2 m_v2Position;
	Vector2 m_v2Scale;
	float m_fRotation;

	Matrix3 m_m3LocalMatrix;
	Matrix3 m_m3GlobalMatrix;

	//Vector2 m_v2Velocity;
	////DEFAULT: 1.f
	//float m_fDrag;
	////DEFAULT: 10.f
	////Object weight to be considered in collision
	//float m_fMass;

	//DEFAULT: true
	//Should the object be drawn
	bool m_bVisible;
	//DEFAULT: false
	//Should the object wrap around the the other side of the screen when it leaves view
	bool m_bWrapAndRespawn;

public:
	GameObject(Vector2 _spawn_position = Vector2{ 0.f,0.f });
	~GameObject();

	//Overridable update function
	//Updates all of its children itself
	virtual void Update(float _delta_time);
	//Overridable draw function
	//Draws all of its children
	//Will not draw any of its children if 'm_bVisible = false'
	virtual void Draw(aie::Renderer2D* _render);


	void SetTexture(aie::Texture* _texture);
	//Sets the color using a 4-byte hex value
	void SetColor(unsigned int _color_hex);
	//Sets the color using 4 1-byte values
	void SetColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
	//Sets the color using floats that range from 0.0f - 1.0f
	void SetColor(float _r, float _g, float _b, float _a);

	void SetPosition(Vector2 _position);
	Vector2 GetPosition();

	void SetScale(Vector2 _scale);
	Vector2 GetScale();

	void SetRotation(float _rotation);
	float GetRotation();

	void SetVisible(bool _visible);
	bool GetVisible();

	void SetWrapAndRespawn(bool _wrap_and_respawn);
	bool GetWrapAndRespawn();

	Matrix3 GetGlobalTransform();
	Matrix3 GetLocalTransform();

	//Add a GameObject to this ones children
	void AddChild(GameObject* _child_object);
	//Remove a Gameobject from this ones children
	void RemoveChild(GameObject* _child_object);

	//Set this GameObject to be the child of another
	void SetParent(GameObject* _parent_object);
	//Remove this GameObject from its parent
	void RemoveParent();
};