// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	// allocate memory for components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera	  = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// set up attachments
	SpringArm->SetupAttachment(RootComponent);
	Camera	 ->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		constexpr bool bComplexSweep = false;
		bool const HasHit = PlayerControllerRef->GetHitResultUnderCursor(
			ECC_Visibility,
			bComplexSweep,
			HitResult);

		if (HasHit)
		{
			constexpr int32 Segments = 100;
			constexpr float Radius = 10.0f;
			constexpr float LifeTime = -1.0f;
			constexpr bool bPersistentLines = false;
			
			DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint,
				Radius,
				Segments,
				FColor::Red,
				bPersistentLines,
				LifeTime);

			RotateTurret(HitResult.ImpactPoint);
		}
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// axis bindings
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),		this, &ATank::Turn);
}

void ATank::Move(float Value)
{
	double  const DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	double  const XOffset   = Value * DeltaTime * MovementSpeed;

	constexpr bool bSweep = true;
	FVector const DeltaLocation(XOffset, 0.0, 0.0);
	AddActorLocalOffset(DeltaLocation, bSweep);
}

void ATank::Turn(float Value)
{
	double const DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	double const YawOffset = Value * DeltaTime * TurnRate;

	constexpr bool bSweep = true;
	FRotator const DeltaRotation(0.0, YawOffset, 0.0);
	AddActorLocalRotation(DeltaRotation, bSweep);
}
