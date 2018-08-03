#pragma once
#include "Actor.h"

#define EXPLOSION_PARTICLE_COUNT 50

class ParticleSystem;

class Explosion : public Actor
{
public:

	Explosion();

	~Explosion();

	void Update(float fDeltaTime) override;

	void Draw(aie::Renderer2D* pRenderer);

	void SetHasEmitted(bool bEmitted);

	void OnCollision(Actor *pCollidingObject, CollisionData *data) override;

private:

	ParticleSystem* m_pParticles;
	bool m_bEmitted;
};

