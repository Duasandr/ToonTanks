// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
	// allocate memory for components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera	  = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// set up attachments
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}
