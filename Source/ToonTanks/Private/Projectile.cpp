// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// allocate memory for components
	ProjectileMesh     = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	
	RootComponent = ProjectileMesh;

	// component defaults
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed	 = 2000.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

bool AProjectile::IsSafeToApplyDamageTo(AActor const * DamagedActor) const
{
	auto const * Owner = GetOwner();
	return Owner && DamagedActor && Owner != DamagedActor && DamagedActor != this;
}

void AProjectile::OnHit(
	UPrimitiveComponent	*HitComp,
	AActor				*OtherActor,
	UPrimitiveComponent	*OtherComp,
	FVector				NormalImpulse,
	FHitResult const	&Hit)
{
	if (IsSafeToApplyDamageTo(OtherActor))
	{
		auto * Instigator = GetOwner()->GetInstigatorController();
		auto * DamageType = UDamageType::StaticClass();
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			Instigator,
			this,
			DamageType);

		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticle,
				GetActorLocation(),
				GetActorRotation());
		}
	}
	Destroy();	
}
