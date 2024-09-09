// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATower();

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly , Category = "Combat")
	float FireRange = 100.0f;
	
	UPROPERTY(EditDefaultsOnly , Category = "Combat")
	float FireRate = 2.0f;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY()
	class ATank* Tank;

	bool InFireRange() const;
	
	void CheckFireCondition();
	
};
