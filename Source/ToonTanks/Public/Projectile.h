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

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem * HitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UParticleSystemComponent * SmokeTrailParticleComponent;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = .5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
	
	/**
	 * @brief Checks if it is safe to apply damage to @b DamagedActor
	 * @param DamagedActor The actor to apply the damage
	 * @return It will return true if @c this has a valid owner, @b DamagedActor is valid and not @c this or the owner.
	 * No friendly fire.  
	 */
	bool IsSafeToApplyDamageTo(AActor const* DamagedActor) const;
	
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
};
