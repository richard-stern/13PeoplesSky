#include "Vector3.h"
#include "Renderer2D.h"
#include <vector>

// Forward declatations...
struct Matrix3;

enum ELayer 
{
	ECOLLISIONLAYER_NONE,
	ECOLLISIONLAYER_PLAYER,
	ECOLLISIONLAYER_BULLET,
	ECOLLISIONLAYER_ROCK,
	ECOLLISIONLAYER_ENEMY,
	ECOLLISIONLAYER_HEALTH
};

struct ColliderNode 
{
	ColliderNode(Vector2 v2LocalOffset, int nConnection);

	~ColliderNode();

	Vector3 m_v3Offset; // Current offset of this node.
	Vector3 m_v3LocalOffset; // Original offset of this node, used as reference for transformations of the collider.

	int m_nConnection; // The index of the node this node is connected to (to form an edge) in the node dynamic array.
};

class Collider 
{
public:

	Collider();

	~Collider();

	/*
	Description: Updates the collider transform using the transform matrix of the object.
	Param:
	    Matrix3* pObjMatrix: The pointer to the matrix of the GameObject/Actor parent of this collider.
	*/
	void UpdateBounds(Matrix3* pObjMatrix);

	/*
	Description: Sets the collision layer of the object.
	Param:
	    Elayer eLayer: The layer to move the object onto.
	*/
	void SetLayer(ELayer eLayer);

	/*
	Description: Draws the collider shape out of lines. (For debug purposes.)
	Param:
	    Vector2 v2Origin: The origin point of the collider (should be the object's position).
		Renderer2D* pRenderer: Pointer to the renderer.
	*/
	void DrawCollider(Vector2 v2Origin, aie::Renderer2D* pRenderer);


	std::vector<ColliderNode*>* m_nodes;
	ELayer m_eLayer;
};