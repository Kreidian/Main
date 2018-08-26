// Fill out your copyright notice in the Description page of Project Settings.

#include "TileController.h"
#include "Classes/Materials/Material.h"


// Sets default values for this component's properties
UTileController::UTileController()
{
	X = Y = -1;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTileController::BeginPlay()
{
	Super::BeginPlay();


	
}


// Called every frame
void UTileController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

UMaterialInstance* UTileController::GetCurrentTeamMat()
{
	if (Team <= 0)
		return DefaultMat;

	if (Team == 1)
	{
		if (locked)
			return MatsTeamOneLocked;
		else
			return MatsTeamOne;
	}

	if (Team == 2)
	{
		if (locked)
			return MatsTeamTwoLocked;
		else
			return MatsTeamTwo;
	}

	return DefaultMat;

	
}

bool UTileController::CanFlip(int32 ateam)
{
	if (Team == ateam)
		return true;

	if (locked == false)
		return true;

	return false;
}

void UTileController::SettAllMaterials(UMaterialInstance * defmat, UMaterialInstance * team1, UMaterialInstance * team1lock, UMaterialInstance * team2, UMaterialInstance * team2Lock)
{
	DefaultMat = defmat;
	MatsTeamOne = team1;
	MatsTeamOneLocked = team1lock;
	MatsTeamTwo = team2;
	MatsTeamTwoLocked = team2Lock;
}



