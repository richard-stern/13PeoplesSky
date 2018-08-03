#include "Explosion.h"
#include "ParticleSystem.h"

Explosion::Explosion()
{
	m_pParticles = new ParticleSystem(EXPLOSION_PARTICLE_COUNT, 0.1f, "./textures/gibs.png");
	m_pParticles->SetEmissionEnabled(false);
	m_pParticles->SetMinMaxLifetime(1.5f, 2.5f);
	m_pParticles->SetMinMaxSpeed(400.0f, 500.0f);
	m_bEmitted = true;
}

Explosion::~Explosion()
{
	delete m_pParticles;
}

void Explosion::Update(float fDeltaTime) 
{
	if(!m_bEmitted) // Only emitt once.
	{
		m_pParticles->Burst(EXPLOSION_PARTICLE_COUNT);
		m_bEmitted = true;
	}

	m_pParticles->SetPosition(m_v2Position);
	m_pParticles->Update(fDeltaTime);
}

void Explosion::Draw(aie::Renderer2D* pRenderer) 
{
	m_pParticles->Draw(pRenderer);
}

void Explosion::SetHasEmitted(bool bEmitted) 
{
	m_bEmitted = bEmitted;
}

void Explosion::OnCollision(Actor *pCollidingObject, CollisionData *data) 
{

}
