#include "Enemy.h"
#include "Player.h"
#include "Rock.h"
#include "Bullet.h"
#include "TextureManager.h"
#include "PursueBehaviour.h"
#include "AvoidBehaviour.h"
#include "CollisionManager.h"
#include "Primitives.h"
#include "GUI.h"
#include "Level.h"
#include <MathF.h>
#include "BulletManager.h"

Enemy::Enemy(Level* pLevel) : Actor()
{
	//Loading texture instance
	TextureManager* TextureManager = TextureManager::GetInstance();
	SetTexture(TextureManager->LoadTexture("./textures/car.png"));

	m_player = pLevel->GetPlayer();
	m_rock = pLevel->GetRocks();
	m_enemy = pLevel->GetEnemies();

	//*slaps top of enemy* this bad boy can take so many bullets
	SetHealth(1);

	//Initialising player variables
	SetMass(0.5f);
	m_maxRot = 2.0f;
	SetMaxHealth(1);

	//The number of rocks in the level is equal to ROCK_COUNT sqrd
	rockCount = ROCK_COUNT * ROCK_COUNT;
	enemyCount = ENEMY_COUNT * ENEMY_COUNT;
	
	//Creating the instances of the enemy's 2 behaviour types
	m_pursue = new PursueBehaviour;
	m_avoid = new AvoidBehaviour;

	CollisionManager* collisionMan = CollisionManager::GetInstance();

	PrimRectangle* collider = new PrimRectangle(36, 42);
	collider->SetLayer(ECOLLISIONLAYER_ENEMY);
	SetCollider(collider);
	collisionMan->AddObject(this);

	//Making sure the enemy is actually drawn to start with
	SetVisible(true);

	SetWrapAndRespawn(true);

	// Shooting
	m_timer = 0.0f;

	m_bulletMan = new BulletManager(this, 5, ECOLLISIONLAYER_ENEMY_BULLET, ECOLLISIONLAYER_ENEMY);
	AddChild(m_bulletMan);
}

Enemy::~Enemy()
{
	//Spring cleaning
	delete m_pursue;
	delete m_avoid;
	delete m_bulletMan;
}

void Enemy::Update(float DeltaTime)
{

	m_timer += DeltaTime;

	//Updates the distance between this class and the player every frame
	m_distToPlayer = m_player->GetPosition() - GetPosition();
	m_lengthToPlayer = m_distToPlayer.magnitude();
	//m_distToRock = pRock->GetPosition().dot(GetPosition());

	//When a destroyed enemy is far enough away from the player, redraw it
	if (m_lengthToPlayer > 800.0f && GetVisible() == false)
	{
		SetVisible(true);
		SetWrapAndRespawn(true);
	}

	//If player is within a certain radius, pursue player. Only pursues if the player is drawn
	if (m_lengthToPlayer < 600.0f && GetVisible() == true)
	{
		//first paramter is the object being sought, 2nd parameter is the pursuer
		// Whilst it's pursuing the player, we want the enemy to try and avoid all of the rocks
		Vector2 pursueForce = m_pursue->update(m_player, this);
		SetVelocity(GetVelocity() + pursueForce * DeltaTime);
	

		// Shooting
		if (m_timer > FIRE_RATE)
		{
			m_timer = 0;

			Vector2 toPlayer = m_player->GetPosition() - m_v2Position;
			toPlayer.normalise();

			m_bulletMan->ShootBullet(m_v2Position, toPlayer);
		}
	}

	//If the enemy has been destroyed, it will flee the player so that it can reach a distance where it can "respawn"
	else if (GetVisible() == false)
	{
		Vector2 avoidForce = m_avoid->update(m_player, this);
		SetVelocity(GetVelocity() + avoidForce * DeltaTime);
	}

	//ROCK AVOIDANCE
	for(int i = 0; i < rockCount; i++)
	{
		//Formula to get the distance between two vectors
		float distBetween = sqrt((powf(GetPosition().x - m_rock[i]->GetPosition().x, 2)) + (powf(GetPosition().y - m_rock[i]->GetPosition().y, 2.0f)));

		if (distBetween <= 100.0f)
		{
			Vector2 avoidForce = m_avoid->update(m_rock[i], this);
			Vector2 pursueForce = m_pursue->update(m_player, this);
			SetVelocity(GetVelocity() + avoidForce * DeltaTime);
		}
	}

	for (int i = 0; i < enemyCount; i++)
	{
		//Formula to get the distance between two vectors
		float distBetween = sqrt((powf(GetPosition().x - m_enemy[i]->GetPosition().x, 2)) + (powf(GetPosition().y - m_enemy[i]->GetPosition().y, 2.0f)));

		if (distBetween <= 30.0f)
		{
			Vector2 avoidForce = m_avoid->update(m_enemy[i], this);
			Vector2 pursueForce = m_pursue->update(m_player, this);
			SetVelocity(GetVelocity() + avoidForce * DeltaTime);
		}
	}

	Actor::Update(DeltaTime);

	//Enemy rotation
	Vector2 v2Facing = GetVelocity();
	v2Facing.normalise();
	SetRotation(atan2(v2Facing.y, v2Facing.x));	
}

//When the enemy collides with another object, rather than being "destroyed", it simply becomes invisible and runs away
void Enemy::OnCollision(Actor* collidingObject, CollisionData* data)
{
	/*Vector2 currentPos = GetPosition();*/
		switch (collidingObject->GetCollider()->GetLayer())
	{
	case(ECOLLISIONLAYER_NONE):
		//failsafe code, shouldn't ever be called
		break;

	case(ECOLLISIONLAYER_PLAYER):
		//When the enemy hits a player, the enemy gets destroyed and the player takes 1 point of damage
		SetVisible(false);
		//Bouncing off the player
		/*currentPos -= data->m_v2Normal * data->m_fPenetration;
		SetVelocity((GetVelocity() - (2 * (GetVelocity().dot(data->m_v2Normal)) * data->m_v2Normal)));*/
		break;

	case(ECOLLISIONLAYER_BULLET):
		//take damage from the bullet, bullet should also be destroyed on impact
		ModifyHealth(-1);
		if (GetHealth() <= 0)
		{
			SetVisible(false);
			SetWrapAndRespawn(true);

			//When the enemy is destroyed, add 5 to the player score
			GUI::GetInstance()->AddScore(200);
		}
		break;

	case(ECOLLISIONLAYER_ROCK):
		//formula for bouncing off of other rocks
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;

	case(ECOLLISIONLAYER_ENEMY):

		//formula for bouncing off of enemies
		m_v2Velocity = (m_v2Velocity - (2 * (m_v2Velocity.dot(data->m_v2Normal)) * data->m_v2Normal));
		break;

	case(ECOLLISIONLAYER_HEALTH):
		//We don't want the enemy to interact with the health pickups at all, so we ignore them
		break;
	}
}

//Simple setter and getter for the object's speed variable
void Enemy::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

float Enemy::GetMaxSpeed()
{
	return m_maxSpeed;
}