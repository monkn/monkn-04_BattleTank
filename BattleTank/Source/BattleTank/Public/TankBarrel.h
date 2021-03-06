// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max down speed, 1 is max up speed
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10.0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElivationDegrees = 40.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElivationDegrees = 0.0;
};
