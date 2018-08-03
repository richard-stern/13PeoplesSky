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

	// override the draw so we can use it to draw animations
	void Draw(aie::Renderer2D* pRenderer) override;
	
	// Does nothing at the moment
	void OnCollision(Actor* collidingObject, CollisionData* data);

protected:
	float m_fMaxSpeed;
	float m_fMaxRot;
	float m_timer;
	float m_fCollisionTime;
	//float m_fStationaryTime;
	float m_fRotationDrag;
	bool m_bPlayerInvincibility;
	//Vector2 m_v2StationaryPos;
	Turret* m_ShipTurret;
	
	// stuff for animation (by cameron :D )
	aie::Texture* m_shipSheet; // spritesheet
	aie::Texture* m_shipSprite; // ship itself
	Vector2 m_shipSize; // single sprite size
	
};