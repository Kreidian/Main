// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Engine/DataTable.h"

#include "LayoutInfo.generated.h"

/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FLevelDefData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FLevelDefData()
		: SizeX(0), SizeY(0), TileSize(0), AIDiff(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Info")
	int32 SizeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Info")
	int32 SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Info")
	int32 Rounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Info")
	int32 TileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Info")
	int32 AIDiff;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIPTRIAL_API ULayoutInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	int32 Xsize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	int32 Ysize;

	// Sets default values for this component's properties
	ULayoutInfo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
