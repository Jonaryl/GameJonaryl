// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Particle_PlayerF.h"

AParticle_PlayerF::AParticle_PlayerF()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AParticle_PlayerF::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT(" Coucou c'est moi la Particle "));

	LaunchParticle();
	if (CollisionAttack && !isCounter)
	{
		CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AParticle_PlayerF::OnAttackCollisionBeginOverlap);
		CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AParticle_PlayerF::OnAttackCollisionEndOverlap);
	}

	float DelayBeforeDestroy = 0.6f;

	if (isSpeTimeDestroy == true)
	{
		DelayBeforeDestroy = speTimeDestroy;
		//UE_LOG(LogTemp, Error, TEXT("DelayBeforeDestroy = %f"), DelayBeforeDestroy);
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			if (isSpeTimeDestroy == true)
			UE_LOG(LogTemp, Error, TEXT("Destroy timer"));
	Destroy();
		}, DelayBeforeDestroy, false);
}
void AParticle_PlayerF::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


////////////////////////// STATS ///////////////////////////
void AParticle_PlayerF::SetAttack_Implementation(FStruct_CharacterStats playerStats, FStruct_HitStats hitStats, AActor* currentPlayer, AActor* enemyLocked)
{

}
void AParticle_PlayerF::IsCountered_Implementation(AActor* EnemyCountered)
{

}

////////////////////////// PARTICLE ///////////////////////////
void AParticle_PlayerF::LaunchParticle()
{
	FVector SpwanedPosition = GetActorLocation();
	FRotator SpwanedRotation = GetActorRotation();

	FVector SpawnedPosition = GetActorLocation() + GetActorForwardVector() * ParticlePosition.X + GetActorRightVector() * ParticlePosition.Y + GetActorUpVector() * ParticlePosition.Z;
	FRotator SpawnedRotation = GetActorRotation() + ParticleRotation;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), particle, SpawnedPosition, SpawnedRotation);
}

////////////////////////// COLLISION ///////////////////////////
void AParticle_PlayerF::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
void AParticle_PlayerF::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void AParticle_PlayerF::DamageEnemy(AEnemy_Unit* enemy)
{

}
