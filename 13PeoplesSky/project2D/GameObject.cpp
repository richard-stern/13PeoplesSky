#include "GameObject.h"

#include "Camera.h"

GameObject::GameObject(Vector2 _spawn_position)
{
	m_pParent = nullptr;

	m_pTexture = nullptr;
	m_iColor = 0xFFFFFFFF; //White
	
	m_v2Position = _spawn_position;
	//m_m3GlobalMatrix.SetPosition(_spawn_position);
	m_v2Scale = Vector2{ 1.f,1.f };
	m_fRotation = 0.f;

	m_bVisible = true;
	m_bWrapAndRespawn = false;
}

GameObject::~GameObject() {}

void GameObject::Update(float _delta_time)
{
	//Construct matrix
	Matrix3 pos, rot, sca;
	pos.SetPosition(m_v2Position);
	rot.SetRotate2D(m_fRotation);
	sca.SetScale(m_v2Scale);
	m_m3LocalMatrix.LocalTransform(pos, rot, sca);
	//Global transform
	if (m_pParent)
		m_m3GlobalMatrix.GlobalTransform(m_pParent->m_m3GlobalMatrix, m_m3LocalMatrix);
	else
		m_m3GlobalMatrix = m_m3LocalMatrix;

	//Run wrap and respawn code
	if (m_bWrapAndRespawn)
		WrapAndRespawn();

	//Update all of our children
	for (auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
	{
		(*iter)->Update(_delta_time);
	}
}

void GameObject::Draw(aie::Renderer2D* _render)
{
	if (m_bVisible)
	{
		_render->setRenderColour(m_iColor);
		//Dont draw it if texture is nullptr
		if (m_pTexture)
			_render->drawSpriteTransformed3x3(m_pTexture, (float*)m_m3GlobalMatrix);
	}
	//Draw all of our children
	for (auto iter = m_Children.begin(); iter != m_Children.end(); ++iter)
	{
		(*iter)->Draw(_render);
	}
}

void GameObject::SetTexture(aie::Texture* _texture)
{
	m_pTexture = _texture;
}

void GameObject::SetColor(unsigned int _color_hex)
{
	m_iColor = _color_hex;
}

void GameObject::SetColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	m_iColor = _r + (_g << 8) + (_b << 16) + (_a << 24);
}

void GameObject::SetColor(float _r, float _g, float _b, float _a)
{
	unsigned char r, g, b, a;

	r = (unsigned char)(_r * 255.f);
	g = (unsigned char)(_g * 255.f);
	b = (unsigned char)(_b * 255.f);
	a = (unsigned char)(_a * 255.f);

	m_iColor = r + (g << 8) + (b << 16) + (a << 24);
}

void GameObject::SetPosition(Vector2 _position)
{
	m_v2Position = _position;
}

Vector2 GameObject::GetPosition()
{
	return m_v2Position;
}

void GameObject::SetScale(Vector2 _scale)
{
	m_v2Scale = _scale;
}

Vector2 GameObject::GetScale()
{
	return m_v2Scale;
}

void GameObject::SetRotation(float _rotation)
{
	m_fRotation = _rotation;
}

float GameObject::GetRotation()
{
	return m_fRotation;
}

void GameObject::SetVisible(bool _visible)
{
	m_bVisible = _visible;
}

bool GameObject::GetVisible()
{
	return m_bVisible;
}

void GameObject::SetWrapAndRespawn(bool _wrap_and_respawn)
{
	m_bWrapAndRespawn = _wrap_and_respawn;
}

bool GameObject::GetWrapAndRespawn()
{
	return m_bWrapAndRespawn;
}

bool GameObject::WrapAndRespawn()
{
	Vector2 camPos = Camera::GetInstance()->GetPosition();
	Vector2 camRes = Camera::GetInstance()->GetResolution();
	////Fix camera position
	camPos += Vector2{ camRes.x / 2.0f, camRes.y / 2.0f };

	Vector2 distance = camPos - m_v2Position;
	bool wrapped = false;

	//X
	if (distance.x > camRes.x)
	{
		m_v2Position.x += camRes.x * 2.0f;
		wrapped = true;
	}
	else if (distance.x < -camRes.x)
	{
		m_v2Position.x -= camRes.x * 2.0f;
		wrapped = true;
	}
	//Y
	if (distance.y > camRes.y)
	{
		m_v2Position.y += camRes.y * 2.0f;
		wrapped = true;
	}
	else if (distance.y < -camRes.y)
	{
		m_v2Position.y -= camRes.y * 2.0f;
		wrapped = true;
	}
	return wrapped;
}

Matrix3 GameObject::GetGlobalTransform()
{
	return m_m3GlobalMatrix;
}

Matrix3 GameObject::GetLocalTransform()
{
	return m_m3LocalMatrix;
}

void GameObject::AddChild(GameObject* _child_object)
{
	////If the child had a previous parent, remove it from the relationship
	//if (_child_object->m_pParent)
	//	_child_object->m_pParent->RemoveChild(_child_object);
	////Make the object know that we are its parent
	//_child_object->m_pParent = this;
	////Add it to our list of children
	//m_Children.push_back(_child_object);
	m_Children.push_back(_child_object);
}

void GameObject::RemoveChild(GameObject* _child_object)
{
	auto iter = m_Children.begin();
	//Search for the child
	for (; iter != m_Children.end(); ++iter)
	{
		//If we find it, remove it
		if ((*iter) == _child_object)
		{
			m_Children.erase(iter);
			break;
		}
	}

}

void GameObject::SetParent(GameObject* _parent_object)
{
	////If we had a parent tell it that we're leaving it
	//if (m_pParent)
	//	m_pParent->RemoveChild(this);
	////Setup our new parent
	//_parent_object->AddChild(this);
	//m_pParent = _parent_object;
	m_pParent = _parent_object;
}

void GameObject::RemoveParent()
{
	//if (m_pParent)
	//{
	//	//Tell the parent we noone longer are part of its children
	//	m_pParent->RemoveChild(this);
	//	m_pParent = nullptr;
	//}
	m_pParent = nullptr;
}