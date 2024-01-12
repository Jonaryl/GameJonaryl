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

	if (isSpecialAttacking)
	{
		timeCurrentSpecialAtk++;
		// Launch Particle
		if (timeCurrentSpecialAtk == timeWhenLaunchParticle[indexParticle])
		{
			UE_LOG(LogTemp, Warning, TEXT(" Launch Particle "));
			LaunchParticle(playerStats, enemyLocked, indexParticle);
		}
		// Enable Damage
		if (timeCurrentSpecialAtk == timeWhenEnableDamage[indexParticle])
		{
			UE_LOG(LogTemp, Warning, TEXT(" Enable Damage "));
			isSpecialAttacking = false;
		}
	}
}


/////////////////////////// START ///////////////////////////
void UComponent_PlayerF_SpeAtk::SpecialAttack(){}

/////////////////////////// START ///////////////////////////
void UComponent_PlayerF_SpeAtk::LaunchParticle(FStruct_CharacterStats playerStatistics, AActor* enemy, int index)
{
	if (!particleSpecials.IsEmpty())
	{
		TSubclassOf<AActor> particle = particleSpecials[index];
		if (particle)
		{
			AActor* OwnerActor = GetOwner();
			AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(particle, OwnerActor->GetActorLocation(), OwnerActor->GetActorRotation());

			AttackInterface = Cast<IParticle_PlayerF_I>(AttackInstance);

			FStruct_HitStats hitStats;
			hitStats.BaseDamage = BaseDamages[index];
			hitStats.ArmorDamage = ArmorDamages[index];
			hitStats.isRightDamage = false;

			if (AttackInterface)
			{
				AttackInterface->Execute_SetAttack(AttackInstance, playerStatistics, hitStats, OwnerActor, enemy);
			}
		}
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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy_Unit::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AEnemy_Unit* EnemyUnit = Cast<AEnemy_Unit>(Actor);
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
	UE_LOG(LogTemp, Warning, TEXT(" SetEnemyLocked "));
	enemyLocked = enemy;
}
void UComponent_PlayerF_SpeAtk::SetPlayerStats(FStruct_CharacterStats playerStatistics)
{
	UE_LOG(LogTemp, Warning, TEXT(" SetPlayerStats "));
	playerStats = playerStatistics;
}

