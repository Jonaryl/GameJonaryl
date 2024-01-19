// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Component_Enemies_Hits.h"

void UComponent_Enemies_Hits::SpawnParticleAttack(FStruct_CharacterStats enemyStats)
{
	if (particle)
	{
		AActor* OwnerActor = GetOwner();
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(particle, OwnerActor->GetActorLocation(), OwnerActor->GetActorRotation());

		AttackInterface = Cast<IParticle_Enemies_I>(AttackInstance);

		FStruct_HitStats hitStats;
		hitStats.BaseDamage = BaseDamage;
		hitStats.ArmorDamage = ArmorDamage;
		hitStats.isRightDamage = isRightDamage;
		
		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, enemyStats, hitStats, OwnerActor);
		}
		
	}
}

////////////////////////// GET ///////////////////////////
void UComponent_Enemies_Hits::GettimeCurrentAttack(float time) { timeCurrentAttack = time; }
bool UComponent_Enemies_Hits::GetisCombo() { return isCombo; }
int UComponent_Enemies_Hits::GetcomboID() { return comboID; }
int UComponent_Enemies_Hits::GetattackID() { return attackID; }
int UComponent_Enemies_Hits::GethitID() { return hitID; }
float UComponent_Enemies_Hits::GettimeWhenHit() { return timeWhenHit; }
float UComponent_Enemies_Hits::GettimeWhenEndHit() { return timeWhenEndHit; }
float UComponent_Enemies_Hits::GettimeWhenLaunchParticle() { return timeWhenLaunchParticle; }
float UComponent_Enemies_Hits::GettimeWhenEnableDamage(){ return timeWhenEnableDamage; }
