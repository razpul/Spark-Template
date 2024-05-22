#include "LevelManager.h"

#include <ranges>

#include "ILevelBase.h"
#include "Spark/Gameplay/GameInstance.h"

LevelManager::LevelManager(GameInstance* _game)
{
	m_config = _game->GetConfig();
	m_screen = _game->GetScreen();
}

LevelManager::~LevelManager()
{
	for (const auto& level : m_levels | std::views::values)
		delete level;

	m_levels.clear();
	m_openLevels.clear();
	m_openListChanges.clear();
}

void LevelManager::Tick(const float _dt)
{
	for (auto& change : m_openListChanges)
		change();

	m_openListChanges.clear();

	for(const auto& level : m_openLevels)
	{
		//level->GetWorld()->Tick(_dt);
		level->Tick(_dt);
	}
}

void LevelManager::Render() const
{
	for(const auto& level : m_openLevels)
	{
		level->Render();
		//level->GetWorld()->Render();
	}
}

void LevelManager::OpenLevel(const char* _name)
{
	if (!m_levels.contains(_name))
		return;

	ILevelBase* level = m_levels[_name];
	if (std::ranges::find(m_openLevels, level) != m_openLevels.end())
		return;

	m_openListChanges.emplace_back([level, this]
		{
			m_openLevels.emplace_back(level);
			level->BeginPlay();
		});
}

void LevelManager::ExitLevel(const char* _name)
{
	if (!m_levels.contains(_name))
		return;

	ILevelBase* level = m_levels[_name];
	if (std::ranges::find(m_openLevels, level) == m_openLevels.end())
		return;

	m_openListChanges.emplace_back([level, this]
		{
			level->EndPlay();
			m_openLevels.remove(level);
		});
}

void LevelManager::AddLevel(ILevelBase* _level)
{
	if (m_levels.contains(_level->Name()))
		return;

	m_levels[_level->Name()] = _level;
	_level->m_levelManager = this;
}

Config* LevelManager::GetConfig() const
{
	//return m_app->GetConfig();
	return m_config;
}

Screen* LevelManager::GetScreen() const
{
	return m_screen;
}
