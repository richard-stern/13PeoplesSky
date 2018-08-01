#include "Collider.h"
#include "Matrix3.h"
#include <cmath>
#include "Vector2.h"

// ColliderNode struct

ColliderNode::ColliderNode(Vector2 v2LocalOffset, int nConnection)
{
	m_v3LocalOffset = Vector3(v2LocalOffset.x, v2LocalOffset.y, 0);
	m_v3Offset = m_v3LocalOffset; // Set current offset to local offset.
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
}

Collider::~Collider() 
{
	delete m_nodes;
}

void Collider::UpdateBounds(Matrix3* pObjMatrix)
{
	std::vector<ColliderNode*>& nodesRef = *m_nodes;

	// Iterate through all nodes and multiply their offsets by the parent object's matrix.
	for (int i = 0; i < nodesRef.size(); ++i)
	{
		ColliderNode& currentNode = *nodesRef[i];

		// Multiply local offset and matrix to create the correctly transformed node offset.
		currentNode.m_v3Offset = *pObjMatrix * currentNode.m_v3LocalOffset;
	}
}

void Collider::SetLayer(ELayer eLayer) 
{
	m_eLayer = eLayer;
}

void Collider::DrawCollider(Vector2 v2Origin ,aie::Renderer2D* pRenderer) 
{
	std::vector<ColliderNode*>& nodesRef = *m_nodes;

	Vector3 v3Origin = Vector3(v2Origin.x, v2Origin.y, 0);

	// Iterate through all nodes and call drawLine() using their offsets.
	for (int i = 0; i < nodesRef.size(); ++i)
	{
		// Get current node and its connected node.
		ColliderNode& currentNode = *nodesRef[i];
		ColliderNode& connectedNode = *nodesRef[currentNode.m_nConnection];
		
		// Get worldspace positions.
		Vector3 v2CurrentNodePos = v3Origin + currentNode.m_v3Offset;
		Vector3 v2ConnectedNodePos = v3Origin + connectedNode.m_v3Offset;

		// Draw line using worldspace positions.
		pRenderer->drawLine(v2CurrentNodePos.x, v2CurrentNodePos.y, v2ConnectedNodePos.x, v2ConnectedNodePos.y);
	}
}
