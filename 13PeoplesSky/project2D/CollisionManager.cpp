#include "CollisionManager.h"
#include "Collider.h"

CollisionManager::CollisionManager()
{
	
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::CreateInstance() 
{
	// Create the singleton instance if it doesn't already exist.
	if (!m_instance)
		m_instance = new CollisionManager;
}

CollisionManager* CollisionManager::GetInstance() 
{
	if (m_instance)
		return m_instance; // Return existing collision manager.
	else
	{
		CreateInstance(); // Create new collision manager.
		return m_instance; // Return new collision manager.
	}
}

void CollisionManager::DestroyInstance() 
{
	// Delete the collision manager if it still exists.
	if (m_instance)
		delete m_instance;

	m_instance = nullptr;
}

CollisionManager* CollisionManager::m_instance = nullptr;
