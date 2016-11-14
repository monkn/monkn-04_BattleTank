// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetControlledPawn()) { return; }

	GetControlledPawn()->DetachFromControllerPendingDestroy();
	Destroy();
	
}

void ATankAIController::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	//if (!ensure(PlayerTank) || !ensure(ControlledTank) || !ensure(AimingComponent)) { return; }
	if (!(PlayerTank) || !ensure(AimingComponent)) { return; }
		
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
	
	MoveToActor(PlayerTank, AcceptanceRadius);
}

