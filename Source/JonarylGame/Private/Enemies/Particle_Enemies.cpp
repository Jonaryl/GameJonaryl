// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Particle_Enemies.h"

AParticle_Enemies::AParticle_Enemies()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AParticle_Enemies::BeginPlay()
{
	Super::BeginPlay();

	LaunchParticle();
	if (CollisionAttack && !isCounter)
	{
		CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AParticle_Enemies::OnAttackCollisionBeginOverlap);
		CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AParticle_Enemies::OnAttackCollisionEndOverlap);
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

void AParticle_Enemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////// STATS ///////////////////////////
void AParticle_Enemies::SetAttack_Implementation(FStruct_CharacterStats enemyStats, FStruct_HitStats hitStats, AActor* currentEnemy)
{

}
void AParticle_Enemies::IsCountered_Implementation(AActor* EnemyCountered)
{

}

////////////////////////// PARTICLE ///////////////////////////
void AParticle_Enemies::LaunchParticle()
{
	FVector SpwanedPosition = GetActorLocation();
	FRotator SpwanedRotation = GetActorRotation();

	FVector SpawnedPosition = GetActorLocation() + GetActorForwardVector() * ParticlePosition.X + GetActorRightVector() * ParticlePosition.Y + GetActorUpVector() * ParticlePosition.Z;
	FRotator SpawnedRotation = GetActorRotation() + ParticleRotation;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), particle, SpawnedPosition, SpawnedRotation);
}

////////////////////////// COLLISION ///////////////////////////
void AParticle_Enemies::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
void AParticle_Enemies::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void AParticle_Enemies::DamageEnemy(APlayerF_Character* player)
{

}