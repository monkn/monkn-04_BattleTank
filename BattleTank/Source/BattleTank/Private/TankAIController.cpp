// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	//if (!ensure(PlayerTank) || !ensure(ControlledTank) || !ensure(AimingComponent)) { return; }
	if (!ensure(PlayerTank) || !ensure(AimingComponent)) { return; }
		
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
	// TODO fix firing
	//ControlledTank->Fire(); // TODO limit firing rate


	MoveToActor(PlayerTank, AcceptanceRadius);
}

