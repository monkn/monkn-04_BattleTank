// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Tank.h"
#include "../Public/TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
	
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire(); // TODO limit firing rate


	MoveToActor(PlayerTank, AcceptanceRadius);
}

