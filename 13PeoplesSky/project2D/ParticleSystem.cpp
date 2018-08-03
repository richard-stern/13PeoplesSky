#include "ParticleSystem.h"
#include "TextureManager.h"
#include "List.h"
#include <iostream>

ParticleSystem::ParticleSystem(int nParticleCount, float fEmissionRate, const char* szImagePath)
{
	m_nParticleCount = nParticleCount;

	// Create containers.
	m_pActiveParticles = new List<Particle*>();
	m_pInactiveParticles = new List<Particle*>();

	// Load texture.
	m_pParticleTexture = TextureManager::GetInstance()->LoadTexture(szImagePath);

	// Set properties.
	m_eVolume = EMITTER_VOLUME_POINT;

	m_fCircleVolRadius = 64.0f;
	m_fEmissionRate = fEmissionRate;
	m_fEmissionTime = m_fEmissionRate;

	m_nRectVolScaleX = 64;
	m_nRectVolScaleY = 64;

	m_bEnabled = true;

	// Initialize particles.
	for(int i = 0; i < m_nParticleCount; ++i) 
	{
		m_pInactiveParticles->Add(new Particle());
	}

	// Initialize particle default values.
	m_fMinSpeed = 300.0f;
	m_fMaxSpeed = m_fMinSpeed;

	m_fMinLifetime = 3.0f;
	m_fMaxLifetime = 3.0f;

	m_fMinRotation = 0.0f;
	m_fMaxRotation = 0.0f;

	m_fMinRotationSpeed = 0.0f;
	m_fMaxRotationSpeed = 0.0f;

	m_bParticleFade = true;
}

ParticleSystem::~ParticleSystem()
{
	for(ListIterator<Particle*> it = m_pActiveParticles->CreateIterator(); !it.AtEnd(); ++it) 
	{
		Particle*& current = it.Value();

		if (current)
		{
			delete current;
			current = nullptr;
		}
	}

	for (ListIterator<Particle*> it = m_pInactiveParticles->CreateIterator(); !it.AtEnd(); ++it)
	{
		Particle*& current = it.Value();

		if (current)
		{
			delete current;
			current = nullptr;
		}
	}

	delete m_pActiveParticles;
	delete m_pInactiveParticles;
}

void ParticleSystem::Update(float fDeltaTime)
{
	// Update particles.
	List<Particle*>& activeRef = *m_pActiveParticles;

	for(ListIterator<Particle*> it = activeRef.CreateIterator(); !it.AtEnd(); ++it) 
	{
		Particle* current = it.Value();
		Particle& currentRef = *current;

		if (currentRef.m_fLifeTime <= 0.0f)
		{
			// Remove particle and add it to the inactive list when it's lifetime expires.
			m_pInactiveParticles->Add(current);
			it.RemoveCurrent();

			continue;
		}

		// Update particle position.
		currentRef.m_m3Matrix.SetPosition(currentRef.m_m3Matrix.GetPosition() + currentRef.m_v2Direction * currentRef.m_fSpeed * fDeltaTime);

		// Update particle rotation.
		currentRef.m_fRotation += currentRef.m_fRotationSpeed * fDeltaTime;
		currentRef.m_m3Matrix.SetRotate2D(currentRef.m_fRotation);

		// Update particle lifetime.
		currentRef.m_fLifeTime -= fDeltaTime;
	}

	m_fEmissionTime -= fDeltaTime;

	// Emitt particles when timer is up.
	if(m_fEmissionTime <= 0.0f && m_pInactiveParticles->Count() > 0 && m_bEnabled)
	{
		// Use iterator to get first particle in the list.
		ListIterator<Particle*> it = m_pInactiveParticles->CreateIterator();

		Particle* newParticle = it.Value();

		InstantiateParticle(newParticle);
		m_pActiveParticles->Add(newParticle);
		it.RemoveCurrent();
		
		m_fEmissionTime = m_fEmissionRate;
	}
}

void ParticleSystem::Burst(int nCount) 
{
	ListIterator<Particle*> it = m_pInactiveParticles->CreateIterator();
	for(int i = 0; i < nCount && !it.AtEnd(); ++i) 
	{
		Particle* newParticle = it.Value();

		InstantiateParticle(newParticle);
		m_pActiveParticles->Add(newParticle);
		it.RemoveCurrent();

		++it;
	}
}

void ParticleSystem::Draw(aie::Renderer2D* pRenderer) 
{
	for (ListIterator<Particle*> it = m_pActiveParticles->CreateIterator(); !it.AtEnd(); ++it)
	{
		if(m_bParticleFade) 
		{
			// Use particle lifetime for alpha transparency. The particle will begin to fade once the lifetime is below 1 second.
			pRenderer->setRenderColour(1.0f, 1.0f, 1.0f, it.Value()->m_fLifeTime);
			pRenderer->drawSpriteTransformed3x3(m_pParticleTexture, (float*)(&it.Value()->m_m3Matrix));
			pRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pRenderer->drawSpriteTransformed3x3(m_pParticleTexture, (float*)(&it.Value()->m_m3Matrix));
		}
	}
}

void ParticleSystem::SetEmissionEnabled(bool bEnabled) 
{
	m_bEnabled = bEnabled;
}

void ParticleSystem::SetEmitterVolumeType(EEmissionVolume eVolume) 
{
	m_eVolume = eVolume;
}

void ParticleSystem::SetParticleLifetimeFade(bool bFade) 
{
	m_bParticleFade = bFade;
}

void ParticleSystem::SetEmissionRate(float fRate) 
{
	m_fEmissionRate = fRate;
}

void ParticleSystem::SetMinMaxSpeed(float fMin, float fMax) 
{
	m_fMinSpeed = fMin;
	m_fMaxSpeed = fMax;
}

void ParticleSystem::SetMinMaxRotation(float fMin, float fMax) 
{
	m_fMinRotation = fMin;
	m_fMaxRotation = fMax;
}

void ParticleSystem::SetMinMaxRotationSpeed(float fMin, float fMax) 
{
	m_fMinRotationSpeed = fMin;
	m_fMaxRotationSpeed = fMax;
}

void ParticleSystem::SetMinMaxLifetime(float fMin, float fMax) 
{
	m_fMinLifetime = fMin;
	m_fMaxLifetime = fMax;
}

void ParticleSystem::InstantiateParticle(Particle* particle)
{
	Particle& particleRef = *particle;

	// Set speed.
	particleRef.m_fSpeed = m_fMinSpeed + (((rand() % 101) / 100) * (m_fMaxSpeed - m_fMinSpeed));

	// Set lifetime.
	particleRef.m_fLifeTime = m_fMinLifetime + (((rand() % 101) / 100) * (m_fMaxLifetime - m_fMinLifetime));

	// Set rotation.
	particleRef.m_fRotation = m_fMinRotation + (((rand() % 101) / 100) * (m_fMaxRotation - m_fMinRotation));

	// Set rotation speed.
	particleRef.m_fRotationSpeed = m_fMinRotationSpeed + (((rand() % 101) / 100) * (m_fMaxRotationSpeed - m_fMinRotationSpeed));

	// Create random unit vector for direction.
	Vector2 v2RandomDir
	(
		-1.0f + (static_cast<float>(rand() % 101) / 50.0f),
		-1.0f + (static_cast<float>(rand() % 101) / 50.0f)
	);

	particleRef.m_v2Direction = v2RandomDir;

	// Set position...
	switch (m_eVolume)
	{
	case EMITTER_VOLUME_POINT:
		particleRef.m_m3Matrix.SetPosition(m_v2Position);
		break;

	case EMITTER_VOLUME_CIRCLE:
		particleRef.m_m3Matrix.SetPosition(m_v2Position + v2RandomDir * m_fCircleVolRadius);
		break;

	case EMITTER_VOLUME_RECTANGLE:

		particleRef.m_m3Matrix.SetPosition
		(
			(m_v2Position.x - static_cast<float>(m_nRectVolScaleX / 2)) + static_cast<float>(rand() % (m_nRectVolScaleX + 1)),
		    (m_v2Position.y - static_cast<float>(m_nRectVolScaleY / 2)) + static_cast<float>(rand() % (m_nRectVolScaleY + 1))
		);
		break;

	default:
		particleRef.m_m3Matrix.SetPosition(m_v2Position);
		break;
	}
}