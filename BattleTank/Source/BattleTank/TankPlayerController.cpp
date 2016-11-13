// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}


void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation(0, 0, 0);	
	if(GetSightRayHitLocation(HitLocation))
	{
			AimingComponent->AimAt(HitLocation);	
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{ 
	HitLocation = FVector(1, 1, 1);
	float MaxDistance = 2000.0;

	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D (ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);


	FVector LookDirection;
	FVector LookPosition;
	if (GetLookDirection(ScreenLocation, LookDirection, LookPosition))
	{
		return GetLookVectorHitLocation(LookDirection, LookPosition, HitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& LookPosition) const
{
	FVector CameraWorldLocation;
	bool ret =  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		LookPosition,
		LookDirection);

	return ret;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector LookPosition, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();	
	auto EndLocation = StartLocation +  LookDirection * LineTraceRange;

	FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("")), true, GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		QueryParams
		))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	
	HitLocation = FVector(0);
	return false;
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Tank Dead!!"));
}