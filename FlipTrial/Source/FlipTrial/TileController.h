// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeamSetEventDelegate, int32, team);

class UMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIPTRIAL_API UTileController : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTileController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FTeamSetEventDelegate OnTeamSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coordinates")
	bool locked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coordinates")
	int32 Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coordinates")
	int32 X;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coordinates")
	int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* DefaultMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* MatsTeamOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* MatsTeamOneLocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* MatsTeamTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* MatsTeamTwoLocked;
	
	UFUNCTION(BlueprintCallable)
	UMaterialInstance* GetCurrentTeamMat();

	UFUNCTION(BlueprintCallable)
	bool CanFlip(int32 ateam);

	UFUNCTION(BlueprintCallable)
	void SettAllMaterials(UMaterialInstance* defmat, UMaterialInstance* team1, UMaterialInstance* team1lock, UMaterialInstance* team2, UMaterialInstance* team2Lock);
};
