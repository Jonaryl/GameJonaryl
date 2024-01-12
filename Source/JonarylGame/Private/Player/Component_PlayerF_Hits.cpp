// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component_PlayerF_Hits.h"


void UComponent_PlayerF_Hits::SpawnParticleAttack(FStruct_CharacterStats playerStats, AActor* enemyLocked)
{
	if (particle)
	{
		AActor* OwnerActor = GetOwner();
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(particle, OwnerActor->GetActorLocation(), OwnerActor->GetActorRotation());

		AttackInterface = Cast<IParticle_PlayerF_I>(AttackInstance);

		FStruct_HitStats hitStats;
		hitStats.BaseDamage = BaseDamage;
		hitStats.ArmorDamage = ArmorDamage;
		hitStats.isRightDamage = isRightDamage;

		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, playerStats, hitStats, OwnerActor, enemyLocked);
		}
	}
}



void UComponent_PlayerF_Hits::GettimeCurrentAttack(float time)
{
	timeCurrentAttack = time;
}
int UComponent_PlayerF_Hits::GetattackID()
{
	return attackID;
}
int UComponent_PlayerF_Hits::GethitID()
{
	return hitID;
}
float UComponent_PlayerF_Hits::GettimeWhenHit()
{
	return timeWhenHit;
}
float UComponent_PlayerF_Hits::GettimeWhenEndHit()
{
	return timeWhenEndHit;
}
float UComponent_PlayerF_Hits::GettimeWhenLaunchParticle()
{
	return timeWhenLaunchParticle;
}
float UComponent_PlayerF_Hits::GettimeWhenEnableDamage()
{
	return timeWhenEnableDamage;
}

