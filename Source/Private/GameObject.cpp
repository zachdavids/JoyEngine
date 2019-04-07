#include "GameObject.h"

void Engine::GameObject::Update()
{
	if (m_Parent)
	{
		m_Transform.SetPosition(m_Parent->m_Transform.GetPosition() + m_Transform.GetLocalPosition());
		m_Transform.SetRotation(m_Parent->m_Transform.GetRotation() * m_Transform.GetLocalRotation());
	}
	else
	{
		m_Transform.SetPosition(m_Transform.GetLocalPosition());
		m_Transform.SetRotation(m_Transform.GetLocalRotation());
	}
}

void Engine::GameObject::AddChild(GameObject* child)
{
	if (!child) { return; }

	m_Children.push_back(child);
}

void Engine::GameObject::AttachTo(GameObject* parent)
{
	if (!parent) { return; }

	m_Parent = parent;
	parent->AddChild(this);
}
