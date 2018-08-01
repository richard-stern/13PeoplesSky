//#include Actor.h
#include "Matrix3.h"
#include "Vector2.h"
#include <Renderer2D.h>
#include <Texture.h>

//class Camera;

class Player //: public Actor
{
public:
	Player();
	~Player();

	void update(float deltTime);
	void draw(aie::Renderer2D* pRenderer);

	int GetHealth();
	//void SetCamera(Camera* LevelCamera);

protected:
	//Camera* m_cLevelCamera;

	// Replace under variables with gameobject's variables
	Matrix3 m_m3LocalMatrix;
	Matrix3 m_m3GlobalMatrix;
	Matrix3 mPosition;
	Vector2 m_v2Velocity;
	float m_fMaxSpeed;
	float m_timer;
	float m_fDrag;
	float m_fMass;
};