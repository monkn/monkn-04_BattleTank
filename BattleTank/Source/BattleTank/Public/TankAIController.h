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
public:
	UFUNCTION()
		void OnPossessedTankDeath();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0;

private:
	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	
};
