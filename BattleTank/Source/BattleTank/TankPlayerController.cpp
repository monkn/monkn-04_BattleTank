// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	


	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		//TankAimingComponent = AimingComponent;
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }
	
	FVector HitLocation(0, 0, 0);
	
	if(GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController - HitLocation: %s"), *HitLocation.ToString());
	}
	// Get world location of linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
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
		if (GetLookVectorHitLocation(LookDirection, LookPosition, HitLocation))
		{
			ATank* MyTank = GetControlledTank();
			if (MyTank)
			{
				MyTank->AimAt(HitLocation);
			}
		}
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