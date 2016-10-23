// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetControlledTank();
	if (Tank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Controlled tank is NULL"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


