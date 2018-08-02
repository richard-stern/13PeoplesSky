#include "CollisionManager.h"
#include "Primatives.h"
#include "Actor.h"

CollisionManager::CollisionManager()
{
	m_actors = new std::vector<Actor*>;
	m_shape1Projections = new std::vector<float>;
	m_shape2Projections = new std::vector<float>;
}

CollisionManager::~CollisionManager()
{
	delete m_shape1Projections;
	delete m_shape2Projections;
	delete m_actors;
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

void CollisionManager::AddObject(Actor* pActor) 
{
	m_actors->push_back(pActor);
}

void CollisionManager::RemoveObject(Actor* pActor) 
{
	std::vector<Actor*>& actorsRef = *m_actors;

	// Iterate through all actors and remove the matching pointer.
	for(int i = 0; i < actorsRef.size(); ++i)
	{
		if (actorsRef[i] == pActor)
		{
			actorsRef.erase(actorsRef.begin() + i);
			return;
		}
	}
}

void CollisionManager::Update() 
{
	std::vector<Actor*>& actorsRef = *m_actors;

	// Iterate through all actors...
	for (int i = 0; i < actorsRef.size(); ++i)
	{
		Actor* currentActor = actorsRef[i];
		Collider* currentCollider = currentActor->GetCollider(); // Will be replaced with GetCollider()

		if (true && currentCollider->GetLayer() != ECOLLISIONLAYER_NONE) // "true" will be replaced with actor is visible..
		{
			// Iterate through all other objects...
			for (int j = 0; j < actorsRef.size(); ++j)
			{
				Actor* otherActor = actorsRef[j];
				Collider* otherCollider = otherActor->GetCollider();

				if(otherActor != currentActor && otherCollider->GetLayer() != currentCollider->GetLayer()) 
				{
					CollisionData data = RunCollisionTest(currentActor, otherActor, currentCollider, otherCollider); // Get collision data.
					if(data.m_bCollided) // If the collision result was positive...
					{
						// Run OnCollision() functions.
						currentActor->OnCollision(otherActor, &data);
						otherActor->OnCollision(currentActor, &data);
					}
				}
			}
		}
	}
}

CollisionData CollisionManager::RunCollisionTest(Actor* pActor1, Actor* pActor2, Collider* pCollider1, Collider* pCollider2)
{
	// SAT...
	CollisionData data;

	// Get node arrays of both colliders.
	const std::vector<ColliderNode*>& collider1Nodes = *pCollider1->GetNodes();
	const std::vector<ColliderNode*>& collider2Nodes = *pCollider2->GetNodes();

	// Iterate through all vertices of both colliders combined.
	for (int i = 0; i < (collider1Nodes.size() + collider2Nodes.size()); ++i)
	{
		m_shape1Projections->clear();
		m_shape2Projections->clear();

		const Collider* selectedCollider = nullptr;

		// Determine if the node is from the first collider or the second.

		Vector2 v2EdgeDir;
		Vector2 v2Axis;

		if (i < collider1Nodes.size())
		{
			// Set selected collider.
			selectedCollider = pCollider1;

			// Get current node.
			ColliderNode* currentNode = collider1Nodes[i];

			// Get edge normal between the current node and it's connection.
			v2EdgeDir = (collider1Nodes[currentNode->m_nConnection]->m_v2Offset - currentNode->m_v2Offset);
			v2EdgeDir.normalise();
		}
		else
		{
			int j = i - collider1Nodes.size();

			// Set selected collider.
			selectedCollider = pCollider2;

			// Get current node.
			ColliderNode* currentNode = collider2Nodes[j];

			// Get edge normal between the current node and it's connection.
			v2EdgeDir = (collider2Nodes[currentNode->m_nConnection]->m_v2Offset - currentNode->m_v2Offset);
			v2EdgeDir.normalise();
		}

		// Set axis to the normal of the edge direction.
		v2Axis = v2EdgeDir.perpCW();
		data.m_v2Normal = v2Axis;

		// Get vector projections and the closet and furthest projections from the axis origin...

		float fShape1CloseDist = INFINITY;
		float fShape1FurthDist = -INFINITY;
		for (int j = 0; j < collider1Nodes.size(); ++j) 
		{
			float fProjection = (pActor1->GetPosition() + collider1Nodes[j]->m_v2Offset).dot(v2Axis);

			// Find closes and furthest projections from axis origin...
			if (fShape1CloseDist > fProjection)
				fShape1CloseDist = fProjection;

			if (fShape1FurthDist < fProjection)
				fShape1FurthDist = fProjection;

			m_shape1Projections->push_back(fProjection);
		}

		float fShape2CloseDist = INFINITY;
		float fShape2FurthDist = -INFINITY;
		for (int j = 0; j < collider2Nodes.size(); ++j)
		{
			float fProjection = (pActor2->GetPosition() + collider2Nodes[j]->m_v2Offset).dot(v2Axis);

			// Find closes and furthest projections from axis origin...
			if (fShape2CloseDist > fProjection)
				fShape2CloseDist = fProjection;

			if (fShape2FurthDist < fProjection)
				fShape2FurthDist = fProjection;

			m_shape2Projections->push_back(fProjection);
		}

		// Check for projection crossovers between the two colliders.
		if (fShape1FurthDist <= fShape2FurthDist && fShape1FurthDist >= fShape2CloseDist) // Intersection scenario
		{
			float fCrossoverSize = fShape1FurthDist - fShape2CloseDist; // Get crossover penetration.

			if (fCrossoverSize < data.m_fPenetration)
				data.m_fPenetration = fCrossoverSize;

			++data.m_nProjectionCrossovers; // Increment crossover count.
		}
		else if (fShape1FurthDist > fShape2FurthDist && fShape2FurthDist >= fShape1CloseDist) // Other intersection scenario
		{
			float fCrossoverSize = fShape2FurthDist - fShape1CloseDist; // Get crossover penetration.

			if (fCrossoverSize < data.m_fPenetration)
				data.m_fPenetration = fCrossoverSize;

			++data.m_nProjectionCrossovers; // Increment crossover count.
		}
		else // Objects are not colliding, bail out.
		{
			data.m_bCollided = false;
			return data;
		}
	}

	return data; // At this point the collision was probably successful.
}

CollisionManager* CollisionManager::m_instance = nullptr;
