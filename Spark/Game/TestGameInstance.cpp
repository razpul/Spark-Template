#include "TestGameInstance.h"

#include <iostream>

#include "LevelNames.h"
#include "TestLevel.h"
#include "Spark/Level/LevelManager.h"

void TestGameInstance::BeginPlay()
{
	if(LevelManager* levelManager = GetLevelManager())
	{
		levelManager->AddLevel(new TestLevel);

		levelManager->OpenLevel(TEST_LEVEL);
	}
}

void TestGameInstance::EndPlay()
{
	std::cout << "End Play!\n";
}
