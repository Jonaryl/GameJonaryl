// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Component_Enemies_Attacks.h"

// Sets default values for this component's properties
UComponent_Enemies_Attacks::UComponent_Enemies_Attacks()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UComponent_Enemies_Attacks::BeginPlay()
{
	Super::BeginPlay();

	
	
}
void UComponent_Enemies_Attacks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


////////////////////////// ATTACK ///////////////////////////
void UComponent_Enemies_Attacks::StartAttack(FStruct_CharacterStats enemyStatistics)
{
	enemyStats = enemyStatistics;

	currentHit = 0;
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT(" attackID = %d"), attackID);
		/*
		UE_LOG(LogTemp, Warning, TEXT(" hit is combo = %s"),isCombo ? TEXT("True") : TEXT("False"));
		*/
		hitList.Empty();

		TInlineComponentArray<UActorComponent*> ComponentList;
		OwnerActor->GetComponents(ComponentList);
		for (UActorComponent* Component : ComponentList)
		{
			UComponent_Enemies_Hits* HitComponent = Cast<UComponent_Enemies_Hits>(Component);
			if (HitComponent)
			{
				if (HitComponent->GetisCombo() == isCombo && attackID == HitComponent->GetattackID() && comboID == HitComponent->GetcomboID())
						hitList.Add(HitComponent);
			}
		}
		hitList.Sort([](UComponent_Enemies_Hits& A, UComponent_Enemies_Hits& B)
			{
				return A.GethitID() < B.GethitID();
			});
			/*
		for (UComponent_Enemies_Hits* Component : hitList)
		{
			UE_LOG(LogTemp, Warning, TEXT(" hit GetisCombo = %s"), Component->GetisCombo() ? TEXT("True") : TEXT("False"));
			UE_LOG(LogTemp, Log, TEXT(" hit comboID = %d"), Component->GetcomboID());
			UE_LOG(LogTemp, Log, TEXT(" hit attackID = %d"), Component->GetattackID());
			UE_LOG(LogTemp, Log, TEXT(" hit hitID = %d"), Component->GethitID());
		}

					UE_LOG(LogTemp, Log, TEXT(" GettimeWhenHit = %f"), hitInstance->GettimeWhenHit());
					UE_LOG(LogTemp, Log, TEXT(" GettimeWhenLaunchParticle = %f"), hitInstance->GettimeWhenLaunchParticle());
					UE_LOG(LogTemp, Log, TEXT(" GettimeWhenEnableDamage = %f"), hitInstance->GettimeWhenEnableDamage());
					UE_LOG(LogTemp, Log, TEXT(" GettimeWhenEndHit = %f"), hitInstance->GettimeWhenEndHit());
			*/
	}
}
void UComponent_Enemies_Attacks::Attack(float timeCurrentAttack)
{
	if (!hitList.IsEmpty())
	{
		if (currentHit >= 0 && currentHit < hitList.Num() && hitList[currentHit])
		{
			hitInstance = hitList[currentHit];
			if (hitInstance)
			{
				// START HIT
				if (timeCurrentAttack == hitInstance->GettimeWhenHit())
				{
					/*
					UE_LOG(LogTemp, Warning, TEXT(" HIT = %d"), currentHit);
					UE_LOG(LogTemp, Warning, TEXT(" HIT ID = %d"), hitInstance->GethitID());
					*/
				}
					/*
				// Launch Particle
				if (timeCurrentAttack == hitInstance->GettimeWhenLaunchParticle())
				{
					UE_LOG(LogTemp, Error, TEXT(" Launch Particle %f"), timeCurrentAttack);
					hitInstance->SpawnParticleAttack(enemyStats);
				}
				// Enable Damage
				if (timeCurrentAttack == hitInstance->GettimeWhenEnableDamage())
				{
					UE_LOG(LogTemp, Error, TEXT(" Enable Damage %f"), timeCurrentAttack);
					hitInstance->ParticleEnableDamage();
				}
					*/
				// END HIT
				if (timeCurrentAttack == hitInstance->GettimeWhenEndHit())
				{
					currentHit++;
				}
			}
		}
	}
}

void UComponent_Enemies_Attacks::LaunchParticle() 
{ 
	hitInstance->SpawnParticleAttack(enemyStats);
}
void UComponent_Enemies_Attacks::EnableDamage() 
{ 
	hitInstance->ParticleEnableDamage();
}

////////////////////////// STATS ///////////////////////////
bool UComponent_Enemies_Attacks::GetisCombo() { return isCombo; }
int UComponent_Enemies_Attacks::GetcomboID() { return comboID; }
int UComponent_Enemies_Attacks::GetattackID() { return attackID; }
float UComponent_Enemies_Attacks::GettimeAttack() { return timeAttack; }
float UComponent_Enemies_Attacks::GettimeNextAttackCombo() { return timeNextAttackCombo; }
float UComponent_Enemies_Attacks::GettimeStopAnim() { return timeStopAnim; }

