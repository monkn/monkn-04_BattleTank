// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	auto ElevationChange = Speed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElivationDegrees, MaxElivationDegrees);

	UE_LOG(LogTemp, Warning, TEXT("ClampedElevation: %f"), Elevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}