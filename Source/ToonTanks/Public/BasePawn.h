// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	/**
	 * @brief Rotates turret mesh in the world space
	 * @param LookAtTarget It is assumed it is a world space vector.
	 * @param DeltaTime Elapsed time in seconds to interpolate the rotation.
	 */
	void RotateTurret(FVector const& LookAtTarget, float DeltaTime) const;

	void Fire();

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurretRotationRate = 5.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent * CapsuleComp; // forward declaration
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent * ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;	// forward declaration

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem * DeathParticle;
};
