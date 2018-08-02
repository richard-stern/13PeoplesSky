#include <Renderer2D.h>
#include <Texture.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Actor.h"

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
	void update(float deltTime);

	// Just renders player for now
	void draw(aie::Renderer2D* pRenderer);

protected:
	float m_fMaxSpeed;
};