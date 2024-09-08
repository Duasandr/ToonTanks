// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Callback that is going to be bound to the damage delegate. 
	 * @param DamagedActor The actor that was damaged by @b DamageCauser
	 * @param Damage The amount of damage taken. 
	 * @param DamageType The custom type of damage dealt.
	 * @param Instigator The controller that possess the @b DamageCauser
	 * @param DamageCauser The actor that caused the damage.
	 */
	UFUNCTION()
	void DamageTaken(
		AActor			  *DamagedActor,
		float			   Damage,
		UDamageType const *DamageType,
		AController		  *Instigator,
		AActor			  *DamageCauser);
private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 1.0f;

	float Health = 0.0f;

	UPROPERTY()
	class AToonTanksGameMode * GameMode;

	FORCEINLINE void SetHealth(float const NewHealth) { Health = NewHealth; }
	FORCEINLINE void FullHeal() { SetHealth(MaxHealth); }
};
