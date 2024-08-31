// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Allocate memory for components
	CapsuleComp			 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	BaseMesh			 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	TurretMesh			 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));

	// assign root and attach components
	RootComponent = CapsuleComp;
	BaseMesh			->SetupAttachment(CapsuleComp);
	TurretMesh			->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector const& LookAtTarget) const
{
	FVector  const TurretLocation = TurretMesh->GetComponentLocation();
	FVector  const ToTarget		  = LookAtTarget - TurretLocation;
	FRotator const Rotator		  = ToTarget.Rotation();
	FRotator const LookAtRotator(0.0, Rotator.Yaw, 0.0);
	TurretMesh->SetWorldRotation(LookAtRotator);
}
