#include <Renderer2D.h>
#include <Texture.h>
#include "Actor.h"

class Turret;
class Collider;
struct CollisionData;

class Player : public Actor
{
public:
	//-----------------------------------------------------------//
	// Constructor : Requesting texture from TextureManager,
	//				 Setting variables(m_m3LocalTransform, 
	//				 m_v2Velocity, m_fMaxSpeed, m_fDrag, 
	//				 m_fMass).
	//-----------------------------------------------------------//
	Player();
	~Player(); // Deleting nothing at the moment

	//-----------------------------------------------------------//
	// Update : Gets instance of input and level camera,
	//			Is responsible for the movement of the player
	//			Calculating player's velocity and rotation(TODO)
	//			Setting Camera's position to move with the player
	//-----------------------------------------------------------//
	void Update(float deltTime);
	
	// Does nothing at the moment
	void OnCollision(Actor* collidingObject, CollisionData* data);

protected:
	float m_fMaxSpeed;
	float m_fMaxRot;
	Turret* m_ShipTurret;
};