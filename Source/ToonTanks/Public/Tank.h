// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 200.0f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 200.0f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;	// forward declaration

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;	// forward declaration

	UPROPERTY()
	APlayerController* PlayerControllerRef;
	
	void Move(float Value);
	void Turn(float Value);
};
