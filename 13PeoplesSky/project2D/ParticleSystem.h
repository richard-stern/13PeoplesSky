#pragma once
#include "Vector2.h"
#include "Matrix3.h"
#include "Renderer2D.h"

class aie::Texture;
class TextureManager;

template<typename T>
class List;

enum EEmissionVolume 
{
	EMITTER_VOLUME_POINT,
	EMITTER_VOLUME_CIRCLE,
	EMITTER_VOLUME_RECTANGLE
};

struct Particle 
{
	Matrix3 m_m3Matrix;
	Vector2 m_v2Direction;
	float m_fLifeTime = 0.0f;
	float m_fRotation = 0.0f;
	float m_fRotationSpeed = 0.0f;
	float m_fSpeed = 0.0f;
};

class ParticleSystem
{
public:

	ParticleSystem(int nParticleCount, float fEmissionRate, const char* szImagePath);

	~ParticleSystem();

	/*
	Description: Updates the particle system and emitts particles.
	Param:
	    float fDeltaTime: deltatime variable.
	*/
	void Update(float fDeltaTime);

	/*
	Description: Emmitts multiple particles at once.
	Param:
	    int nCount: The amount of particles to emitt.
	*/
	void Burst(int nCount);

	/*
	Description: Draws all active particles to the screen.
	Param:
	    aie::Renderer2D* pRenderer: Pointer to the bootstrap renderer.
	*/
	void Draw(aie::Renderer2D* pRenderer);

	/*
	Description: Sets whether or not passive emission is enabled. (DOES NOT EFFECT BURST CALLS)
	Param:
	    bool bEnable: Future status to of the emitter.
	*/
	void SetEmissionEnabled(bool bEnable);

	/*
	Description: Sets the volume type used for particle emission.
	Param:
	    EEmissionVolume eVolume: The volume type to use.
	*/
	void SetEmitterVolumeType(EEmissionVolume eVolume);

	/*
	Description: Sets whether or not particles fade with lifetime.
	Param:
	    bool bFade: Whether or not particles will fade with lifetime.
	*/
	void SetParticleLifetimeFade(bool bFade);

	/*
	Description: Sets the emission rate of the particle emitter.
	Param:
	    float fRate: The emission rate of the particle emitter.
	*/
	void SetEmissionRate(float fRate);

	/*
	Description: Sets the minimum and maximum speed values for emitted particles.
	Param:
	    float fMin: The minimum value.
		float fMax: The maximum value.
	*/
	void SetMinMaxSpeed(float fMin, float fMax);

	/*
	Description: Sets the minimum and maximum rotation values for emitted particles.
	Param:
	    float fMin: The minimum value.
	    float fMax: The maximum value.
	*/
	void SetMinMaxRotation(float fMin, float fMax);

	/*
	Description: Sets the minimum and maximum rotation speed values for emitted particles.
	Param:
	    float fMin: The minimum value.
	    float fMax: The maximum value.
	*/
	void SetMinMaxRotationSpeed(float fMin, float fMax);

	/*
	Description: Sets the minimum and maximum lifetime values for emitted particles.
	Param:
	    float fMin: The minimum value.
	    float fMax: The maximum value.
	*/
	void SetMinMaxLifetime(float fMin, float fMax);

private:

	void InstantiateParticle(Particle* particle);

	// Particle container...
	List<Particle*>* m_pActiveParticles;
	List<Particle*>* m_pInactiveParticles;

	// Particle system properties...
	Vector2 m_v2Position;
	EEmissionVolume m_eVolume;
	float m_fCircleVolRadius;
	float m_fEmissionRate;
	float m_fEmissionTime;
	int m_nRectVolScaleX;
	int m_nRectVolScaleY;
	int m_nParticleCount;
	bool m_bEnabled;

	// Particle properties...
	aie::Texture* m_pParticleTexture;
	float m_fMinSpeed;
	float m_fMaxSpeed;
	float m_fMinRotation;
	float m_fMaxRotation;
	float m_fMinRotationSpeed;
	float m_fMaxRotationSpeed;
	float m_fMinLifetime;
	float m_fMaxLifetime;
	bool m_bParticleFade;
};

