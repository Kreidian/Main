// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "TileController.h"


bool UGameManager::MapHasUnlockedTile(int32 team)
{
	UTileController* tile;

	for (int x = 0; x < mapWidth; ++x)
	{
		for (int y = 0; y < mapHeight; ++y)
		{
			tile = TilesMap[x].Tiles[y];

			if (tile->Team != team && !tile->locked)
				return true;
		}
	}
	return false;
}

int UGameManager::AISelectionScore(int32 x, int32 y, int32 team)
{
	int score = 0;
	UTileController* temp;

	temp = TilesMap[x].Tiles[y];

	if (temp->Team != team && temp->locked)
		return 0;

	for (int i = 0; i < mapWidth; ++i)
	{
		temp = TilesMap[i].Tiles[y];

		if (temp->Team != team && !temp->locked)
		{
			++score;
		}
	}

	for (int i = 0; i < mapHeight; ++i)
	{
		temp = TilesMap[x].Tiles[i];

		if (temp->Team != team && !temp->locked)
		{
			++score;
		}
	}

	return score;
}

// Sets default values for this component's properties
UGameManager::UGameManager()
	: TilesMap()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	currentTeamTurn = 1;
	gameOver = false;
}


// Called when the game starts
void UGameManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (scorePerTile < 1)
		scorePerTile = 1;
}


// Called every frame
void UGameManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGameManager::CreateTileField(int32 width, int32 height)
{
	mapWidth = width;
	mapHeight = height;

	TilesMap.SetNum(width);
	
	for (int i = 0; i < width; ++i)
	{
		TilesMap[i].Tiles.SetNum(height);
	}

	currentTeamTurn = 1;
	gameOver = false;

	maxScore = mapWidth * mapHeight * scorePerTile;
}

void UGameManager::AddTile(UTileController * tile, int32 x, int32 y)
{
	TilesMap[x].Tiles[y] = tile;

	UTileController* test = TilesMap[x].Tiles[y];

	test->X = x;
	test->Y = y;
}

void UGameManager::FlipTile(UTileController* tile, int32 team)
{
	if (tile == nullptr)
		return;

	int x = tile->X;
	int y = tile->Y;
	UTileController* temp;

	if (tile->Team != team && tile->locked)
		return;

	if (tile->Team == team)
	{
		tile->locked = !(tile->locked);
	}
	else if (!tile->locked)
	{
		tile->Team = team;
		tile->locked = true;
	}

	tile->OnTeamSet.Broadcast(team);

	for (int i = 0; i < mapWidth; ++i)
	{
		temp = TilesMap[i].Tiles[y];

		if (temp->Team == team)
		{
			temp->locked = !(temp->locked);
			temp->OnTeamSet.Broadcast(team);
		}
		else if (!temp->locked)
		{
			temp->Team = team;
			temp->OnTeamSet.Broadcast(team);
		}
	}

	for (int i = 0; i < mapHeight; ++i)
	{
		temp = TilesMap[x].Tiles[i];

		if (temp->Team == team)
		{
			temp->locked = !(temp->locked);
			temp->OnTeamSet.Broadcast(team);
		}
		else if (!temp->locked)
		{
			temp->Team = team;
			temp->OnTeamSet.Broadcast(team);
		}
	}

}

int32 UGameManager::GetCurrentScore(int32 Team)
{
	int32 score = 0;

	for (int i = 0; i < mapWidth; ++i)
	{
		for (int n = 0; n < mapHeight; ++n)
		{
			if (TilesMap[i].Tiles[n]->Team == Team)
				++score;
		}
	}

	return score * scorePerTile;
}

bool UGameManager::CanBeginTurn(int32 Team)
{
	if (currentTeamTurn != Team)
		return false;

	if (gameOver)
		return false;

	if (Team == 1)
	{
		currentTeamTurn = 2;
	}
	else if (Team == 2)
	{
		currentTeamTurn = 1;
		++currentRound;
	}

	return true;
}

void UGameManager::SimulateAITurn(int32 Team)
{
	int x, y, sx, sy;
	UTileController* tile = nullptr;
	bool selecting = true;
	bool filter = true;
	bool xUp = (bool)(FMath::Rand() % 2);
	bool yUp = (bool)(FMath::Rand() % 2);

	switch (AIDifficulty)
	{
	case EAIDiff::AI_EASY:
		x = FMath::Rand() % mapWidth;
		y = FMath::Rand() % mapHeight;

		tile = TilesMap[x].Tiles[y];

		while (tile->Team != Team && tile->locked)
		{
			x = FMath::Rand() % mapWidth;
			y = FMath::Rand() % mapHeight;

			tile = TilesMap[x].Tiles[y];
		}
		break;
	case EAIDiff::AI_MED:
		selecting = true;
		sx = FMath::Rand() % mapWidth;
		sy = FMath::Rand() % mapHeight;

		tile = TilesMap[sx].Tiles[sy];

		filter = MapHasUnlockedTile(Team);

		if (filter)	{
			if (tile->Team != Team && !tile->locked)
				selecting = false;
		} else {
			if (!(tile->Team != Team && tile->locked))
				selecting = false;
		}

		x = sx;
		y = sy;

		for (int i = 0; i < mapWidth && selecting; ++i)
		{
			x = x + (xUp ? 1 : -1);
			if (x < 0) x = mapWidth;
			if (x >= mapWidth) x = 0;

			for (int l = 0; l < mapHeight && selecting; ++l)
			{
				y = y + (yUp ? 1 : -1);
				if (y < 0) y = mapHeight;
				if (y >= mapHeight) y = 0;

				if (selecting)
				{
					tile = TilesMap[x].Tiles[y];

					if (filter) {
						if (tile->Team != Team && !tile->locked)
							selecting = false;
					}
					else {
						if (!(tile->Team != Team && tile->locked))
							selecting = false;
					}
				}
			}
		}

		break;
	case EAIDiff::AI_HARD:
		x = 0;
		y = 0;
		sx = -1;

		for (int i = 0; i < mapWidth; ++i)
		{
			for (int l = 0; l < mapHeight; ++l)
			{
				tile = TilesMap[i].Tiles[l];
				sy = AISelectionScore(i, l, Team);

				if (sx == -1 || sy > sx)
				{
					x = i;
					y = l;
					sx = sy;
				}
			}
		}

		tile = TilesMap[x].Tiles[y];

		break;
	default:
		break;
	}

	FlipTile(tile, Team);
}

bool UGameManager::CheckForGameOver()
{
	if (gameOver)
		return true;

	team1Score = GetCurrentScore(1);
	team2Score = GetCurrentScore(2);

	if (maxRounds > 0 && currentRound >= maxRounds)
	{
		gameOver = true;
		return true;
	}

	if (team1Score == maxScore)
	{
		gameOver = true;
		return true;
	}

	return false;
}

int32 UGameManager::GetWinner()
{
	if (gameOver)
	{
		if (team1Score > team2Score)
			return 1;
		else if (team2Score > team1Score)
			return 2;
		else
			return 0;
	}

	return -1;
}
