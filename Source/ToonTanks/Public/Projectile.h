// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement; // forward declaration

	/**
	 * @brief Callback that is bound to the multicast object managing hit events.
	 * @param HitComp		The component that hit (@c this)
	 * @param OtherActor	The actor that was hit by @b HitComp
	 * @param OtherComp		The component hit by @b HitComp
	 * @param NormalImpulse The Physics Engine response to the hit (direction + magnitude)
	 * @param Hit			Additional information about the Hit event.
	 * See documentation
	 * <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/FHitResult/__ctor/6?application_version=5.4">here</a>
	 * for more details.
	 */
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent * HitComp,
		AActor				* OtherActor,
		UPrimitiveComponent * OtherComp,
		FVector				NormalImpulse,
		FHitResult const	& Hit);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = .5f;
};
