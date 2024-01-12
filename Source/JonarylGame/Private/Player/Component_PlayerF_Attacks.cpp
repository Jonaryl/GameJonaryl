// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component_PlayerF_Attacks.h"

UComponent_PlayerF_Attacks::UComponent_PlayerF_Attacks()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
} 
void UComponent_PlayerF_Attacks::BeginPlay()
{
	Super::BeginPlay();

	currentHit = 0;
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT(" attackID = %d"), attackID);
		//TArray<UActorComponent*> ComponentList = OwnerActor->GetComponentsByClass(UComponent_PlayerF_Hits::StaticClass());
		TInlineComponentArray<UActorComponent*> ComponentList;
		OwnerActor->GetComponents(ComponentList);
		for (UActorComponent* Component : ComponentList)
		{
			UComponent_PlayerF_Hits* HitComponent = Cast<UComponent_PlayerF_Hits>(Component);
			if (HitComponent)
			{
				if(attackID == HitComponent->GetattackID())
					hitList.Add(HitComponent);
			}
		}
		hitList.Sort([](UComponent_PlayerF_Hits& A, UComponent_PlayerF_Hits& B)
			{
				return A.GethitID() < B.GethitID();
			});
		for (UComponent_PlayerF_Hits* Component : hitList)
		{
			UE_LOG(LogTemp, Log, TEXT(" hit attackID = %d"), Component->GetattackID());
			UE_LOG(LogTemp, Log, TEXT(" hit hitID = %d"), Component->GethitID());
		}
	}
	
} 
void UComponent_PlayerF_Attacks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComponent_PlayerF_Attacks::StartAttack(AActor* enemy, FStruct_CharacterStats playerStatistics)
{
	enemyLocked = enemy;
	playerStats = playerStatistics;

	timeCurrentAttack = 0;
	currentHit = 0;
	UE_LOG(LogTemp, Warning, TEXT(" timeCurrentAttack StartAttack = %f"), timeCurrentAttack);
}
void UComponent_PlayerF_Attacks::Attack()
{
	timeCurrentAttack++;
	if (!hitList.IsEmpty())
	{
		if (currentHit >= 0 && currentHit < hitList.Num() && hitList[currentHit])
		{
			UComponent_PlayerF_Hits* hitInstance =  hitList[currentHit];
			if (hitInstance)
			{
				// START HIT
				if (timeCurrentAttack == hitInstance->GettimeWhenHit())
				{
					UE_LOG(LogTemp, Warning, TEXT(" HIT = %d"), currentHit);
					UE_LOG(LogTemp, Warning, TEXT(" HIT ID = %d"), hitInstance->GethitID());
				}
				// Launch Particle
				if (timeCurrentAttack == hitInstance->GettimeWhenLaunchParticle())
				{
					UE_LOG(LogTemp, Warning, TEXT(" Launch Particle "));
					hitInstance->SpawnParticleAttack(playerStats, enemyLocked);
				}
				// Enable Damage
				if (timeCurrentAttack == hitInstance->GettimeWhenEnableDamage())
				{
					UE_LOG(LogTemp, Warning, TEXT(" Enable Damage "));
				}
				// END HIT
				if (timeCurrentAttack == hitInstance->GettimeWhenEndHit())
				{
					currentHit++;
					UE_LOG(LogTemp, Warning, TEXT(" END HIT currentHit = %d"), currentHit);
				}
			}
		}
	}
}


void UComponent_PlayerF_Attacks::SetEnemyLocked(AActor* enemy)
{
	UE_LOG(LogTemp, Warning, TEXT(" SetEnemyLocked "));
	enemyLocked = enemy;
}
void UComponent_PlayerF_Attacks::SetPlayerStats(FStruct_CharacterStats playerStatistics)
{
	UE_LOG(LogTemp, Warning, TEXT(" SetPlayerStats "));
	playerStats = playerStatistics;
}

int UComponent_PlayerF_Attacks::GetattackID()
{
	return attackID;
}
float UComponent_PlayerF_Attacks::GettimeCurrentAttack()
{
	return timeCurrentAttack;
}
float UComponent_PlayerF_Attacks::GettimeAttack()
{
	return timeAttack;
}
float UComponent_PlayerF_Attacks::GettimeWhenCanMove()
{
	return timeWhenCanMove;
}
float UComponent_PlayerF_Attacks::GettimeWhenCanContinueCombo()
{
	return timeWhenCanContinueCombo;
}
float UComponent_PlayerF_Attacks::GettimeWhenStopCombo()
{
	return timeWhenStopCombo;
}
float UComponent_PlayerF_Attacks::GettimeWhenStopAnim(){	return timeWhenStopAnim; }