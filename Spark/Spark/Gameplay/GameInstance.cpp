#include "GameInstance.h"
#include "Spark/Level/LevelManager.h"

GameInstance::GameInstance()
	: m_config{ nullptr }, m_screen{ nullptr }, m_levelManager{nullptr}
{
}

GameInstance::~GameInstance()
{
	delete m_levelManager;
	m_levelManager = nullptr;
}

void GameInstance::BeginPlay()
{
}

void GameInstance::EndPlay()
{
}

Config* GameInstance::GetConfig() const
{
	return m_config;
}

Screen* GameInstance::GetScreen() const
{
	return m_screen;
}

LevelManager* GameInstance::GetLevelManager() const
{
	return m_levelManager;
}

void GameInstance::Init()
{

	m_levelManager = new LevelManager(this);
}

void GameInstance::Tick(const float _dt) const
{
	m_levelManager->Tick(_dt);
}

void GameInstance::Render() const
{
	m_levelManager->Render();

}
