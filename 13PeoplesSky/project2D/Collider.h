#include "Vector3.h"
#include "Vector2.h"
#include "Renderer2D.h"
#include <vector>

// Forward declarations...
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

	Vector2 m_v2Offset; // Current offset of this node.
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
	Description: Sets the collision layer of this collider.
	Param:
	    Elayer eLayer: The layer to move the object onto.
	*/
	void SetLayer(ELayer eLayer);

	/*
	Description: Returns the collision layer value of this collider.
	Return Type: ELayer (VALUE)
	*/
	ELayer GetLayer();

	/*
	Description: Sets the collision layer for this collider to ignore.
	Param:
	    Elayer eLayer: The layer for this object to ignore during collision detection.
	*/
	void SetIgnoreLayer(ELayer eLayer);

	/*
	Description: Returns the collision layer that this collider will ignore.
	Return Type: ELayer (VALUE)
	*/
	ELayer GetIgnoreLayer();

	/*
	Description: Draws the collider shape out of lines. (For debug purposes.)
	Param:
	    Vector2 v2Origin: The origin point of the collider (should be the object's position).
		Renderer2D* pRenderer: Pointer to the renderer.
	*/
	void DrawCollider(Vector2 v2Origin, aie::Renderer2D* pRenderer);

	/*
	Description: Returns a pointer to the nodes of this collider.
	Return Type: std::vector<ColliderNode*>* (PTR)
	*/
	std::vector<ColliderNode*>* GetNodes();

protected:

	std::vector<ColliderNode*>* m_nodes;

	ELayer m_eLayer;
	ELayer m_eIgnoreLayer;
};