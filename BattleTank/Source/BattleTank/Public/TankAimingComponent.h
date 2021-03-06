// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Setup), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	


	UFUNCTION(BlueprintCallable, category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

	EFiringState GetFiringState() const;
	void AimAt(FVector WorldSpaceAim);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 MaxAmmo = 3;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;



	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0;


	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;
	
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();
	
};
