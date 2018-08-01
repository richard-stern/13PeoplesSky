#pragma once

// Forward declarations...
class Collider;

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

private:

	static CollisionManager* m_instance;
};

