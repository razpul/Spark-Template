#include "ActorWorld.h"

#include "Actor.h"

void ActorWorld::Spawn(Actor* _actor, Actor* _parent)
{
	AddActor(_actor, _parent == nullptr ? m_root : _parent);
}

void ActorWorld::SpawnWithTransform(Actor* _actor, const Vec2& _pos, float _rot, const Vec2& _scale, Actor* _parent)
{
	_actor->SetActorTransform(Mat3::CreateTransform(_pos, _rot, &_scale));
	AddActor(_actor, _parent == nullptr ? m_root : _parent);
}

void ActorWorld::Destroy(Actor* _actor)
{
	RemoveActor(_actor);
}

ActorWorld::ActorWorld()
	: m_root{new Actor}, m_config {nullptr}, m_screen {nullptr}
{
}

ActorWorld::~ActorWorld()
{
	delete m_root;
	m_root = nullptr;
}

void ActorWorld::Tick(float _dt)
{
	for (auto& change : m_worldChanges)
		change();

	m_worldChanges.clear();

	if (m_root)
		m_root->Tick(_dt);
}

void ActorWorld::Render() const
{
	if (m_root)
		m_root->Render();
}

void ActorWorld::AddActor(Actor* _actor, Actor* _parent)
{
	m_worldChanges.emplace_back([_actor, _parent, this]
		{
			_actor->m_config = m_config;
			_actor->m_screen = m_screen;

			_actor->SetParent(_parent);
			_actor->ApplyListChanges();

			_actor->OnBeginPlay();
		});
}

void ActorWorld::RemoveActor(Actor* _actor)
{
	m_worldChanges.emplace_back([_actor, this]
		{
			_actor->OnEndPlay();
			delete _actor;
		});
}
