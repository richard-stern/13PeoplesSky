#include "Collider.h"
#include "Matrix3.h"
#include <cmath>
#include "Vector2.h"

// ColliderNode struct

ColliderNode::ColliderNode(Vector2 v2LocalOffset, int nConnection)
{
	m_v3LocalOffset = Vector3(v2LocalOffset.x, v2LocalOffset.y, 0);
	m_v2Offset = v2LocalOffset; // Set current offset to local offset.
	m_nConnection = nConnection;
}

ColliderNode::~ColliderNode() 
{

}

// Collider class

Collider::Collider() 
{
	m_nodes = new std::vector<ColliderNode*>();
	m_eLayer = ECOLLISIONLAYER_NONE;
	m_eIgnoreLayer = ECOLLISIONLAYER_NONE;
}

Collider::~Collider() 
{
	for (unsigned int i = 0; i < m_nodes->size(); ++i)
	{
		delete (*m_nodes)[i];
	}
	
	delete m_nodes;
}

void Collider::UpdateBounds(Matrix3* pObjMatrix)
{
	std::vector<ColliderNode*>& nodesRef = *m_nodes;

	// Iterate through all nodes and multiply their offsets by the parent object's matrix.
	for (unsigned int i = 0; i < nodesRef.size(); ++i)
	{
		ColliderNode& currentNode = *nodesRef[i];

		// Multiply local offset and matrix to create the correctly transformed node offset.
		Vector3 v3TransformedVec = *pObjMatrix * currentNode.m_v3LocalOffset;
		currentNode.m_v2Offset = static_cast<Vector2>(v3TransformedVec);
	}
}

void Collider::SetLayer(ELayer eLayer) 
{
	m_eLayer = eLayer;
}

ELayer Collider::GetLayer() 
{
	return m_eLayer;
}

void Collider::SetIgnoreLayer(ELayer eLayer) 
{
	m_eIgnoreLayer = eLayer;
}

ELayer Collider::GetIgnoreLayer() 
{
	return m_eIgnoreLayer;
}

void Collider::DrawCollider(Vector2 v2Origin ,aie::Renderer2D* pRenderer) 
{
	std::vector<ColliderNode*>& nodesRef = *m_nodes;

	// Iterate through all nodes and call drawLine() using their offsets.
	for (unsigned int i = 0; i < nodesRef.size(); ++i)
	{
		// Get current node and its connected node.
		ColliderNode& currentNode = *nodesRef[i];
		ColliderNode& connectedNode = *nodesRef[currentNode.m_nConnection];
		
		// Get worldspace positions.
		Vector2 v2CurrentNodePos = v2Origin + currentNode.m_v2Offset;
		Vector2 v2ConnectedNodePos = v2Origin + connectedNode.m_v2Offset;

		// Draw line using worldspace positions.
		pRenderer->drawLine(v2CurrentNodePos.x, v2CurrentNodePos.y, v2ConnectedNodePos.x, v2ConnectedNodePos.y);
	}
}

std::vector<ColliderNode*>* Collider::GetNodes() 
{
	return m_nodes;
}
