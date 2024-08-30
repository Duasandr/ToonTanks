// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	// allocate memory for components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera	  = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// set up attachments
	SpringArm->SetupAttachment(RootComponent);
	Camera	 ->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float Value)
{
	double  const DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	double  const XOffset   = Value * DeltaTime * MovementSpeed;

	constexpr bool bSweep = true;
	FVector const DeltaLocation(XOffset, 0.0f, 0.0f);
	AddActorLocalOffset(DeltaLocation, bSweep);
}
