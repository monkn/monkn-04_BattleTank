// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0;

private:
	void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	
};
