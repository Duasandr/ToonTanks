// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

void ABasePawn::HandleDestruction()
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticle,
			GetActorLocation(),
			GetActorRotation());
	}
}

void ABasePawn::RotateTurret(FVector const& LookAtTarget, float DeltaTime) const
{
	FVector  const TurretLocation = TurretMesh->GetComponentLocation();
	FVector  const ToTargetVector = LookAtTarget - TurretLocation;

	FRotator const CurrentRotator = TurretMesh->GetComponentRotation();
	FRotator const ToTargetRotator= ToTargetVector.Rotation();
	// we only want the Yaw component, the turret does not tilt.
	FRotator const Target(0.0, ToTargetRotator.Yaw, 0.0);

	FRotator const NewRotator = FMath::RInterpTo(
		CurrentRotator,
		Target,
		DeltaTime,
		TurretRotationRate
	);
	TurretMesh->SetWorldRotation(NewRotator);
}

void ABasePawn::Fire()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector  const Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator const Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
		auto * ProjectileSpawned = World->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
		ProjectileSpawned->SetOwner(this);
	}
}
