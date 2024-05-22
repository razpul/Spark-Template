#pragma once

#include "Spark/Gameplay/GameInstance.h"

class TestGameInstance final : public GameInstance
{
protected:
	void BeginPlay() override;
	void EndPlay() override;
};

