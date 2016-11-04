// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Public/TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("Tank-CPP Constructor"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	
}


void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);


	
}


void ATank::Fire()
{/*
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (!Barrel)
	{

		UE_LOG(LogTemp, Warning, TEXT("No Barrel"));
	}
	if (Barrel && bIsReloaded && ProjectileBlueprint) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
	*/
}