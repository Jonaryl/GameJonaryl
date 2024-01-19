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

	currentHit = 0;
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT(" attackID = %d"), attackID);

		TInlineComponentArray<UActorComponent*> ComponentList;
		OwnerActor->GetComponents(ComponentList);
		for (UActorComponent* Component : ComponentList)
		{
			UComponent_Enemies_Hits* HitComponent = Cast<UComponent_Enemies_Hits>(Component);
			if (HitComponent)
			{
				if (HitComponent->GetisCombo() == false)
				{
					if (attackID == HitComponent->GetattackID())
						hitList.Add(HitComponent);
				}
				else
				{
					if (attackID == HitComponent->GetattackID() && comboID == HitComponent->GetcomboID())
						hitList.Add(HitComponent);
				}
			}
		}
		hitList.Sort([](UComponent_Enemies_Hits& A, UComponent_Enemies_Hits& B)
			{
				return A.GethitID() < B.GethitID();
			});
		for (UComponent_Enemies_Hits* Component : hitList)
		{
			UE_LOG(LogTemp, Log, TEXT(" hit comboID = %d"), Component->GetcomboID());
			UE_LOG(LogTemp, Log, TEXT(" hit attackID = %d"), Component->GetattackID());
			UE_LOG(LogTemp, Log, TEXT(" hit hitID = %d"), Component->GethitID());
		}
	}
	
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
}
void UComponent_Enemies_Attacks::Attack(float timeCurrentAttack)
{
	if (!hitList.IsEmpty())
	{
		if (currentHit >= 0 && currentHit < hitList.Num() && hitList[currentHit])
		{
			UComponent_Enemies_Hits* hitInstance = hitList[currentHit];
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
					hitInstance->SpawnParticleAttack(enemyStats);
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


////////////////////////// STATS ///////////////////////////
bool UComponent_Enemies_Attacks::GetisCombo() { return isCombo; }
int UComponent_Enemies_Attacks::GetcomboID() { return comboID; }
int UComponent_Enemies_Attacks::GetattackID() { return attackID; }
float UComponent_Enemies_Attacks::GettimeAttack() { return timeAttack; }
float UComponent_Enemies_Attacks::GettimeNextAttackCombo() { return timeNextAttackCombo; }
float UComponent_Enemies_Attacks::GettimeStopAnim() { return timeStopAnim; }

