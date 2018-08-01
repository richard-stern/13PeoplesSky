#pragma once

#include <list>

#include <Renderer2D.h>

#include "Vector2.h"
#include "Matrix3.h"

class GameObject
{
private:
	GameObject* m_pParent;
	std::list<GameObject*> m_Children;

protected:
	aie::Texture* m_pTexture;
	//DEFAULT: White
	//Hex value for the color
	unsigned int m_iColor;

	Vector2 m_v2Position;
	Vector2 m_v2Scale;
	float m_fRotation;

	Matrix3 m_m3LocalMatrix;
	Matrix3 m_m3GlobalMatrix;

	Vector2 m_v2Velocity;
	//DEFAULT: 1.f
	float m_fDrag;

	//DEFAULT: true
	//Should the object be drawn
	bool m_bVisible;
	//DEFAULT: true
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

	void SetPosition(Vector2 _position);
	Vector2 GetPosition();

	void SetScale(Vector2 _scale);
	Vector2 GetScale();

	void SetRotation(float _rotation);
	float GetRotation();

	void SetVelocity(Vector2 _velocity);
	Vector2 GetVelocity();

	void SetDrag(float _drag);
	float GetDrag();

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

	//Collision Resolution
	//This should be overwritten
	virtual void OnCollision(GameObject* _other);
};