// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameManager.generated.h"

class UTileController;

USTRUCT()
struct FieldTiles {
	GENERATED_USTRUCT_BODY()

		UPROPERTY() TArray<UTileController*> Tiles;

	FieldTiles() { }
};

UENUM(BlueprintType)	//"BlueprintType" is essential to include 
enum class EAIDiff : uint8 
{
	AI_EASY UMETA(DisplayName = "Easy"),
	AI_MED 	UMETA(DisplayName = "Medium"),
	AI_HARD	UMETA(DisplayName = "Hard") 
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIPTRIAL_API UGameManager : public UActorComponent
{
	GENERATED_BODY()

private:
	//All Flower Fields on The Island 
	TArray<FieldTiles> TilesMap;
	int32 mapWidth;
	int32 mapHeight;
	int32 maxScore;

	bool gameOver;

	bool MapHasUnlockedTile(int32 team);
	int AISelectionScore(int32 x, int32 y, int32 team);

public:	
	// Sets default values for this component's properties
	UGameManager();

	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	int32 team1Score;

	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	int32 team2Score;

	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	int32 currentTeamTurn;

	UPROPERTY(BlueprintReadOnly, Category = "Game State")
	int32 currentRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State") 
	int32 maxRounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	int32 scorePerTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	EAIDiff AIDifficulty;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void CreateTileField(int32 width, int32 height);
	
	UFUNCTION(BlueprintCallable)
	void AddTile(UTileController* tile, int32 x, int32 y);

	UFUNCTION(BlueprintCallable)
	void FlipTile(UTileController* tile, int32 team);

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentScore(int32 Team);

	UFUNCTION(BlueprintCallable)
	bool CanBeginTurn(int32 Team);

	UFUNCTION(BlueprintCallable)
	void SimulateAITurn(int32 Team);

	UFUNCTION(BlueprintCallable)
	bool CheckForGameOver();

	UFUNCTION(BlueprintCallable)
	int32 GetWinner();
};
