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

	static FRandomStream RandomStreamInt(FMath::Rand());
	damageID = RandomStreamInt.FRandRange(10000000, 999999999);

	CollisionAttack = AParticle_PlayerF::FindComponentByClass<UBoxComponent>();
	if (CollisionAttack)
	{
		FVector SpawnedPosition = GetActorLocation() + GetActorForwardVector() * ColisionPosition.X + GetActorRightVector() * ColisionPosition.Y + GetActorUpVector() * ColisionPosition.Z;
		FRotator SpawnedRotation = GetActorRotation() + ColisionRotation;

		CollisionAttack->SetWorldLocation(SpawnedPosition);
		CollisionAttack->SetWorldRotation(SpawnedRotation);

		if (!isCounter)
		{
			CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AParticle_PlayerF::OnAttackCollisionBeginOverlap);
			CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AParticle_PlayerF::OnAttackCollisionEndOverlap);
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

	if (isOnlyView)
		LaunchParticle();
}
void AParticle_PlayerF::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


////////////////////////// STATS ///////////////////////////
void AParticle_PlayerF::SetAttack_Implementation(FStruct_CharacterStats playerStats, FStruct_HitStats hitStats, AActor* currentPlayer, AActor* enemyLocked)
{
	currentPlayerStats = playerStats;
	currentHitStats = hitStats;
	player = Cast<APlayerF_Character>(currentPlayer);

	if (enemyLocked)
	{
		if (enemyLocked != nullptr && enemyLocked->IsA(AEnemies_Unit::StaticClass()))
		{
			currentEnemyLocked = Cast<AEnemies_Unit>(enemyLocked);
		}
	}
	LaunchParticle();
	if (isSpeSlow)
		EnableDamage_Implementation();
}
void AParticle_PlayerF::IsCountered_Implementation(AActor* EnemyCountered)
{
	LaunchParticle();
	if (EnemyCountered)
	{
		if (EnemyCountered->IsA(AEnemies_Unit::StaticClass()))
		{
			AEnemies_Unit* enemy = Cast<AEnemies_Unit>(EnemyCountered);
			if (enemy)
			{
				enemy->CounterTake();
			}
		}
	}
}

////////////////////////// PARTICLE ///////////////////////////
void AParticle_PlayerF::LaunchParticle()
{
	FVector SpawnedPosition = GetActorLocation() + GetActorForwardVector() * ParticlePosition.X + GetActorRightVector() * ParticlePosition.Y + GetActorUpVector() * ParticlePosition.Z;
	FRotator SpawnedRotation = GetActorRotation() + ParticleRotation;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), particle, SpawnedPosition, SpawnedRotation);
}

////////////////////////// COLLISION ///////////////////////////
void AParticle_PlayerF::EnableDamage_Implementation()
{
	if (CollisionAttack)
	{
		CollisionAttack->SetGenerateOverlapEvents(true);

		CollisionAttack->SetBoxExtent(CollisionSize);
	}
}

void AParticle_PlayerF::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(AEnemies_Unit::StaticClass()))
		{
			AEnemies_Unit* enemy = Cast<AEnemies_Unit>(OtherActor);
			if (enemy)
			{
				if (isSpeSlow)
				{
					enemy->SlowDownTake();
					if (player)
					{
						player->PostProcessSlowActivate(true);
					}
				}
				else
				{
					if (!isOnlyView)
					{
						DamageEnemy(enemy);
						SendMessagesManager(enemy);
					}
					//Destroy();
				}
			}
		}
	}
}
void AParticle_PlayerF::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){}


void AParticle_PlayerF::DamageEnemy(AEnemies_Unit* enemy)
{
	//////////////////// HIT DIRECTION //////////////////////
	bool finalDirectionIsRight;
	FVector enemyAttackDirection = enemy->GetActorLocation();
	FVector PlayerToEnemy = GetActorLocation() - enemyAttackDirection;
	PlayerToEnemy.Normalize();

	FVector PlayerForwardVector = enemy->GetActorForwardVector();
	FVector PlayerRightVector = enemy->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(PlayerToEnemy, PlayerForwardVector);
	float RightDot = FVector::DotProduct(PlayerToEnemy, PlayerRightVector);

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
	{
			// Le coup vient de derriere
		if (ForwardDot < 0)
		{
			finalDirectionIsRight = !currentHitStats.isRightDamage;
			//UE_LOG(LogTemp, Error, TEXT("dos dos dos dos "));
		}
			// Le coup vient de devant
		else
		{
			finalDirectionIsRight = currentHitStats.isRightDamage;
			//UE_LOG(LogTemp, Error, TEXT("face face face face "));
		}
	}
	else
	{
			// Le coup vient de la gauche
		if (RightDot < 0)
		{
			finalDirectionIsRight = false;
			//UE_LOG(LogTemp, Error, TEXT("gauche gauche gauche gauche "));
		}
			// Le coup vient de la droite
		else
		{
			finalDirectionIsRight = true;
			//UE_LOG(LogTemp, Error, TEXT("droite droite droite droite "));
		}
	}
	/////////////////////////////////////////////////////////

	//////////////////// DAMAGE //////////////////////
	FStruct_CharacterStats enemyStats = enemy->GetEnemyStats();
	int FinalDamage = currentPlayerStats.Attack + currentHitStats.BaseDamage - enemyStats.Defense;
	if (FinalDamage < 0)
		FinalDamage = 0;

	/*
	UE_LOG(LogTemp, Log, TEXT(" currentPlayerStats.Attack  %f"), currentPlayerStats.Attack);
	UE_LOG(LogTemp, Log, TEXT(" currentHitStats.BaseDamage  %f"), currentHitStats.BaseDamage);
	UE_LOG(LogTemp, Log, TEXT(" enemyStats.Defense  %f"), enemyStats.Defense);
	UE_LOG(LogTemp, Log, TEXT(" FinalDamage  %d"), FinalDamage);
	UE_LOG(LogTemp, Log, TEXT(" currentHitStats.ArmorDamage  %f"), currentHitStats.ArmorDamage);
	*/

	enemy->DamageTake(FinalDamage, finalDirectionIsRight, currentHitStats.isCutFromDamage, currentHitStats.ArmorDamage, damageID);
	/////////////////////////////////////////////////////////


	//////////////////// EDIT HUD VIEWED //////////////////////
	if (currentEnemyLocked)
	{
		UE_LOG(LogTemp, Log, TEXT(" 111111 currentEnemyLocked"));
		if (currentEnemyLocked->GetEnemyId() == enemy->GetEnemyId())
		{
			UE_LOG(LogTemp, Log, TEXT(" 22222222 currentEnemyLocked->GetEnemyId() == enemy->GetEnemyId()"));
			FStruct_CharacterStats enemyLockedStats = currentEnemyLocked->GetEnemyStats();

			player->EditEnemyHealth(enemyLockedStats.MaxHealth, enemyLockedStats.Health);
			player->EditEnemyArmor(enemyLockedStats.MaxArmor, enemyLockedStats.Armor);
			if (enemyLockedStats.Health <= 0)
			{
			UE_LOG(LogTemp, Log, TEXT(" 33333  enemyLockedStats.Health <= 0"));
				player->EnemyHudIsVisible(false);
				player->EnemyLockedIsDead();
			}
			else
				player->EnemyHudIsVisible(true);
		}
	}
	/////////////////////////////////////////////////////////
}

void AParticle_PlayerF::SendMessagesManager(AEnemies_Unit* enemy)
{
	FStruct_DeathData currentEnemy = enemy->GetDeathData();
	if (currentEnemy.isDead == true && currentEnemy.hasSendDeadMessage == false)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScene_EnemiesManager::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			enemiesManager = Cast<AScene_EnemiesManager>(Actor);
		}
		if (enemiesManager)
		{
			enemiesManager->EnemyIsDead(currentEnemy.id, currentEnemy.idZone, currentEnemy.idWave);
			enemy->SethasSendDeadMessage(true);
		}
	}
}
