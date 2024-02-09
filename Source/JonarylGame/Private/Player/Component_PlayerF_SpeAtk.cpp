// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component_PlayerF_SpeAtk.h"

// Sets default values for this component's properties
UComponent_PlayerF_SpeAtk::UComponent_PlayerF_SpeAtk()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UComponent_PlayerF_SpeAtk::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
void UComponent_PlayerF_SpeAtk::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isSpecialAttacking && !timeWhenLaunchParticle.IsEmpty())
	{
		timeCurrentSpecialAtk++;
		//UE_LOG(LogTemp, Log, TEXT("SPE ATK timeCurrentSpecialAtk %f"), timeCurrentSpecialAtk);
		// Launch Particle
		if (timeCurrentSpecialAtk == timeWhenLaunchParticle[indexParticle])
		{
			//UE_LOG(LogTemp, Warning, TEXT("SPE ATK Launch Particle  %f"), timeCurrentSpecialAtk);
			LaunchParticle(playerStats, enemyLocked, indexParticle);
		}
		// Enable Damage
		if (timeCurrentSpecialAtk == timeWhenEnableDamage[indexParticle])
		{
			//UE_LOG(LogTemp, Warning, TEXT("SPE ATK Enable Damage  %f"), timeCurrentSpecialAtk);
			AllEnemyEndSlow();
			EnableDamage();
		}
		// END Anim
		if (timeCurrentSpecialAtk == timeWhenEndAnim[indexParticle])
		{
			//UE_LOG(LogTemp, Warning, TEXT("SPE ATK END Anim %f"), timeCurrentSpecialAtk);
			isSpecialAttacking = false;
			EndSpecialAttack();
		}
	}
}


/////////////////////////// START ///////////////////////////
void UComponent_PlayerF_SpeAtk::SpecialAttack(bool launchParticle){} 
void UComponent_PlayerF_SpeAtk::EndSpecialAttack(){}

/////////////////////////// PARTICLE ///////////////////////////
void UComponent_PlayerF_SpeAtk::LaunchParticle(FStruct_CharacterStats playerStatistics, AActor* enemy, int index)
{
	if (!particleSpecials.IsEmpty())
	{
		TSubclassOf<AActor> particle = particleSpecials[index];
		if (particle)
		{
			AActor* OwnerActor = GetOwner();
			AttackInstance = GetWorld()->SpawnActor<AActor>(particle, OwnerActor->GetActorLocation(), OwnerActor->GetActorRotation());

			AttackInterface = Cast<IParticle_PlayerF_I>(AttackInstance);

			FStruct_HitStats hitStats;
			hitStats.BaseDamage = BaseDamages[index];
			hitStats.ArmorDamage = ArmorDamages[index];
			hitStats.isRightDamage = false;
			hitStats.isCutFromDamage = true;

			if (AttackInterface)
			{
				AttackInterface->Execute_SetAttack(AttackInstance, playerStatistics, hitStats, OwnerActor, enemy);
			}
		}
	}
}
void UComponent_PlayerF_SpeAtk::LaunchSuperModeParticle()
{
	if (particleSuperMode)
	{
		AActor* OwnerActor = GetOwner();
		AActor* SuperModeInstance = GetWorld()->SpawnActor<AActor>(particleSuperMode, OwnerActor->GetActorLocation(), OwnerActor->GetActorRotation());

		AttackInterface = Cast<IParticle_PlayerF_I>(SuperModeInstance);

		FStruct_HitStats hitStats;
		hitStats.BaseDamage = 0;
		FStruct_CharacterStats playerStatistics;
		playerStatistics.Health = 0;

		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(SuperModeInstance, playerStatistics, hitStats, OwnerActor, OwnerActor);
		}
	}
}

void UComponent_PlayerF_SpeAtk::EnableDamage() 
{
	if (AttackInterface)
	{
		AttackInterface->Execute_EnableDamage(AttackInstance);
	}
}
/////////////////////////// SLOW MOTION ///////////////////////////
void UComponent_PlayerF_SpeAtk::StartSlowMotion(float slowStrength)
{
	UWorld* World = this->GetWorld();
	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings)
	{
		WorldSettings->SetTimeDilation(slowStrength);
	}
}
void UComponent_PlayerF_SpeAtk::EndSlowMotion()
{
	UWorld* World = this->GetWorld();
	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings)
	{
		WorldSettings->SetTimeDilation(1.0f);
	}
}
void UComponent_PlayerF_SpeAtk::AllEnemyEndSlow()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemies_Unit::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AEnemies_Unit* EnemyUnit = Cast<AEnemies_Unit>(Actor);
		if (EnemyUnit)
		{
			EnemyUnit->EndSlowMode();
		}
	}
}

/////////////////////////// INPUT ///////////////////////////
void UComponent_PlayerF_SpeAtk::ABtnActionSpe(){}
void UComponent_PlayerF_SpeAtk::BBtnActionSpe(){}
void UComponent_PlayerF_SpeAtk::XBtnActionSpe(){}
void UComponent_PlayerF_SpeAtk::YBtnActionSpe(){}

/////////////////////////// TOOL ///////////////////////////
void UComponent_PlayerF_SpeAtk::GetPlayer(AActor* player){}
void UComponent_PlayerF_SpeAtk::SetEnemyLocked(AActor* enemy)
{
	enemyLocked = enemy;
}
void UComponent_PlayerF_SpeAtk::SetPlayerStats(FStruct_CharacterStats playerStatistics)
{
	UE_LOG(LogTemp, Warning, TEXT(" SetPlayerStats "));
	playerStats = playerStatistics;
}

