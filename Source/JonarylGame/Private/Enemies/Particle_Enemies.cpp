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

	static FRandomStream RandomStreamInt(FMath::Rand());
	damageID = RandomStreamInt.FRandRange(10000000, 999999999);

	LaunchParticle();
	CollisionAttack = AParticle_Enemies::FindComponentByClass<UBoxComponent>();
	if (CollisionAttack)
	{
		FVector SpawnedPosition = GetActorLocation() + GetActorForwardVector() * ColisionPosition.X + GetActorRightVector() * ColisionPosition.Y + GetActorUpVector() * ColisionPosition.Z;
		FRotator SpawnedRotation = GetActorRotation() + ColisionRotation;

		CollisionAttack->SetWorldLocation(SpawnedPosition);
		CollisionAttack->SetWorldRotation(SpawnedRotation);

		if (!isCounter)
		{
			CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AParticle_Enemies::OnAttackCollisionBeginOverlap);
			CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AParticle_Enemies::OnAttackCollisionEndOverlap);
		}
		CollisionAttack->SetGenerateOverlapEvents(false);
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
			//UE_LOG(LogTemp, Error, TEXT("Destroy timer"));
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
	currentEnemyStats = enemyStats;
	currentHitStats = hitStats;
	thisEnemy = currentEnemy;
}
void AParticle_Enemies::IsCountered_Implementation(AActor* playerCountered)
{
	LaunchParticle();
	if (playerCountered)
	{
		APlayerF_Character* PlayerCharacter = Cast<APlayerF_Character>(playerCountered);
		if (PlayerCharacter)
		{
			PlayerCharacter->CounterTake();
		}
	}
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
	if (OtherActor)
	{
		if (OtherActor->IsA(APlayerF_Character::StaticClass()))
		{
			APlayerF_Character* PlayerCharacter = Cast<APlayerF_Character>(OtherActor);
			if (PlayerCharacter)
			{
				DamagePlayer(PlayerCharacter);
			}
		}
	}
}
void AParticle_Enemies::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}


void AParticle_Enemies::EnableDamage_Implementation()
{

	if (CollisionAttack)
	{
		CollisionAttack->SetGenerateOverlapEvents(true);

		CollisionAttack->SetBoxExtent(CollisionSize);
	}
}

void AParticle_Enemies::DamagePlayer(APlayerF_Character* player)
{
	//////////////////// HIT DIRECTION //////////////////////
	bool finalDirectionIsRight;
	FVector playerAttackDirection = player->GetActorLocation();
	FVector PlayerToEnemy = GetActorLocation() - playerAttackDirection;
	PlayerToEnemy.Normalize();

	FVector EnemyForwardVector = player->GetActorForwardVector();
	FVector EnemyRightVector = player->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(PlayerToEnemy, EnemyForwardVector);
	float RightDot = FVector::DotProduct(PlayerToEnemy, EnemyRightVector);

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
	{
		if (ForwardDot < 0)
		{
			// Le coup vient de derriere
			//UE_LOG(LogTemp, Error, TEXT("dos dos dos dos "));
			finalDirectionIsRight = !currentHitStats.isRightDamage;
		}
		else
		{
			// Le coup vient de devant
			//UE_LOG(LogTemp, Error, TEXT("face face face face "));
			finalDirectionIsRight = currentHitStats.isRightDamage;
		}
	}
	else
	{
		if (RightDot < 0)
		{
			// Le coup vient de la gauche
			//UE_LOG(LogTemp, Error, TEXT("gauche gauche gauche gauche "));
			finalDirectionIsRight = false;
		}
		else
		{
			// Le coup vient de la droite
			//UE_LOG(LogTemp, Error, TEXT("droite droite droite droite "));
			finalDirectionIsRight = true;
		}
	}
	/////////////////////////////////////////////////////////

	//////////////////// DAMAGE //////////////////////
	FStruct_CharacterStats playerStats = player->GetPlayerStats();
	int FinalDamage = currentEnemyStats.Attack + currentHitStats.BaseDamage - playerStats.Defense;
	if (FinalDamage < 0)
		FinalDamage = 0;

	player->DamageTake(FinalDamage, finalDirectionIsRight, currentHitStats.isCutFromDamage, thisEnemy, currentHitStats.ArmorDamage, damageID);
	/////////////////////////////////////////////////////////
}