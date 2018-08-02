#pragma once
#include <vector>
#include "Vector2.h"

// Forward declarations...
class Collider;
class Actor;

struct CollisionData 
{
	Vector2 m_v2Normal;
	float m_fPenetration = INFINITY;
	int m_nProjectionCrossovers = 0;
	bool m_bCollided = true;
};

class CollisionManager
{
public:

	CollisionManager();

	~CollisionManager();

	/*
	Description: Creates the singleton instance of the collision manager.
	*/
	static void CreateInstance();

	/*
	Description: Get a pointer to the singleton instance of the collision manager.
	Return Type: CollisionManager* (PTR)
	*/
	static CollisionManager* GetInstance();

	/*
	Description: Delete the singleton instance of the collision manager.
	*/
	static void DestroyInstance();

	/*
	Description: Add an object to the collision manager to run collision detection on.
	Param:
	    Actor* pActor: Pointer to the actor object to be added.
	*/
	void AddObject(Actor* pActor);

	/*
	Description: Remove an object from the collision manager effectively disabling its collision.
	Params:
	    Actor* pActor: Pointer to the actor object to be removed.
	*/
	void RemoveObject(Actor* pActor);

	/*
	Description: Update world collision detection between all added actor objects.
	*/
	void Update();

private:

	/*
	Description: Runs a collision test between the two objects and returns the results.
	Return Type: CollisionData (VALUE)
	Param:
	    Actor* pActor1: The first actor.
		Actor* pActor2: The second actor.
	    Collider* pCollider1: The collider of the first actor. 
		Collider* pCollider2: The collider of the second actor.
	*/
	CollisionData RunCollisionTest(Actor* pActor1, Actor* pActor2, Collider* pCollider1, Collider* pCollider2);

	/*
	Description: Prints information about a collision to the console.
	Param:
	    Actor* pActor1: The first actor.
		Actor* pActor2: The second actor.
	    Collider* pCollider1: The collider of the first actor. 
		Collider* pCollider2: The collider of the second actor.
	*/
	void PrintCollisionInfo(Collider* pCollider1, Collider* pCollider2);

	static CollisionManager* m_instance;

	std::vector<Actor*>* m_actors;
	std::vector<float>* m_shape1Projections;
	std::vector<float>* m_shape2Projections;
};

