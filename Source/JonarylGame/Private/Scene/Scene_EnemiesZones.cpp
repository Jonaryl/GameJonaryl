// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/Scene_EnemiesZones.h"


void AScene_EnemiesZones::Begin()
{
	currentWave = 0;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScene_EnemiesSpawner::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AScene_EnemiesSpawner* EnemySpawn = Cast<AScene_EnemiesSpawner>(Actor);
		if (EnemySpawn)
		{
			if (EnemySpawn->GetidZone() == idZone)
			{
				static FRandomStream RandomStreamInt(FMath::Rand());
				int currentiD = RandomStreamInt.FRandRange(10000000, 999999999);

				EnemySpwaner currentEnemySpawn;
				currentEnemySpawn.idSpwaner = currentiD;

				currentEnemySpawn.enemySpawn = EnemySpawn;
				currentEnemySpawn.idWave = EnemySpawn->GetidWave();
				currentEnemySpawn.isEnemyDead = false;
				currentEnemySpawn.isEnemySpawner = false;

				allEnemySpanwer.Add(currentEnemySpawn);
				EnemySpawn->SetId(currentiD);
			}
		}
	}

	CollisionAttack = AScene_EnemiesZones::FindComponentByClass<UBoxComponent>();
	if (CollisionAttack)
	{
		CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AScene_EnemiesZones::OnAttackCollisionBeginOverlap);
		CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AScene_EnemiesZones::OnAttackCollisionEndOverlap);
	}
}

void AScene_EnemiesZones::SpawnEnemies(int wave)
{
	for (EnemySpwaner spawner : allEnemySpanwer)
	{
		if (spawner.idWave == wave)
		{
			spawner.enemySpawn->SpawnEnemy();
			spawner.isEnemySpawner = true;
			enemySpawned.Add(spawner);
		}
	}
	if (enemySpawned.IsEmpty())
		isActive = false;
}
void AScene_EnemiesZones::CheckIsEnemiesDead(int idEnemy, int wave)
{
	//// MAKE ENEMY DEAD
	for (EnemySpwaner& spawner : enemySpawned)
	{
		if (spawner.idSpwaner == idEnemy && spawner.idWave == wave)
		{
			spawner.isEnemyDead = true;
			spawner.enemySpawn->DeleteEnemy();
			break;
		}
	}
	CheckAllEnemiesDeath(wave);
}

void AScene_EnemiesZones::CheckAllEnemiesDeath(int wave)
{
	int currentDeadCount = 0;
	//// CHECK WHO IS DEAD
	for (EnemySpwaner spawner : enemySpawned)
	{
		if (spawner.isEnemyDead == true && spawner.idWave == wave)
		{
			currentDeadCount++;
		}
	}
	CheckIsAllDead(currentDeadCount);
}

void AScene_EnemiesZones::CheckIsAllDead(int currentDeadCount)
{
	int currentEnemyCount = enemySpawned.Num();
	//// IF ALL ENEMIES ARE DEAD
	if (currentEnemyCount == currentDeadCount)
	{
		currentWave++;
		enemySpawned.Empty();
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
			{
				SpawnEnemies(currentWave);
			}, 1.5f, false);
	}
}




void AScene_EnemiesZones::SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState)
{
	for (EnemySpwaner spawner : enemySpawned)
	{
		if (spawner.isEnemyDead == false)
		{
			spawner.enemySpawn->SharePlayerState(playerState);
		}
	}
}


void AScene_EnemiesZones::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	*/
	if (OtherActor)
	{
		if (OtherActor->IsA(APlayerF_Character::StaticClass()))
		{
			APlayerF_Character* PlayerCharacter = Cast<APlayerF_Character>(OtherActor);
			if (PlayerCharacter && isActive == false)
			{
				isActive = true;
				currentWave++;
				SpawnEnemies(currentWave);
				CollisionAttack->SetGenerateOverlapEvents(false);
			}
		}
	}
}

void AScene_EnemiesZones::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(APlayerF_Character::StaticClass()))
		{
			APlayerF_Character* PlayerCharacter = Cast<APlayerF_Character>(OtherActor);
			if (PlayerCharacter)
			{

			}
		}
	}
	/*
	*/
}

bool AScene_EnemiesZones::GetisActive() { return isActive; }
int AScene_EnemiesZones::GetidZone() { return idZone; }