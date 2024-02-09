// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Unit.h"

////////////////////////////////////////////////////////////////
/////////////////////////  ANIMATION ///////////////////////////
/// EVENT ///
void AEnemies_Unit::EventAnim()
{
	UE_LOG(LogTemp, Error, TEXT("_____EventAnim______"));
}

void AEnemies_Unit::LaunchParticle()
{
	Super::LaunchParticle();
}
void AEnemies_Unit::EnableDamage()
{
	Super::EnableDamage();
}
void AEnemies_Unit::CounterTake()
{
	Super::CounterTake();
}
void AEnemies_Unit::EndSlowMode()
{
	Super::EndSlowMode();
}

/// METHOD
void AEnemies_Unit::StopAllActions()
{ 
	Super::StopAllActions();

	isIdle = false;
	isMoving = false;
	xyMovingValue = FVector(0, 0, 0);

	isDash = false;

	isDamaged = false;

	isCounterPose = false;
	isCounter = false;
	isCounterTake = false;
}





/// VARIABLE ///
//MOVE
bool AEnemies_Unit::GetisIdle() { return isIdle; }
bool AEnemies_Unit::GetisMoving() { return isMoving; }
float AEnemies_Unit::GetxMoving() { return xyMovingValue.X * 100; }
float AEnemies_Unit::GetyMoving() { return xyMovingValue.Y * 100; }

//ATTACK
bool AEnemies_Unit::GetisAttackStarted() { return isAttackStarted; }
int AEnemies_Unit::GetcurrentHitCombo() { return currentHitCombo; }
bool AEnemies_Unit::GetisAttackCombo() { return isAttackCombo; }

///DASH
bool AEnemies_Unit::GetisDash() { return isDash; }

//COUNTER
/*
bool AEnemies_Unit::GetisCounterPose() { return isCounterPose; }
bool AEnemies_Unit::GetisCounter() { return isCounter; }


*/

//DAMAGE
bool AEnemies_Unit::GetisDamaged() { return isDamaged; }
bool AEnemies_Unit::GetisRightAttackHit() { return isRightAttackHit; }

bool AEnemies_Unit::GetisCounterTake() { return isCounterTake; }
bool AEnemies_Unit::GetisSlowDownTake() { return isSlowDownTake; }

int AEnemies_Unit::GethitCountDamageAnimation() { return hitCountDamageAnimation; }

float AEnemies_Unit::GetDmgBlendAlpha() { return DmgBlendAlpha; }
float AEnemies_Unit::GetDmgBlendR() { return DmgBlendR; }
float AEnemies_Unit::GetDmgBlendL() { return DmgBlendL; }

////////////////////////////////////////////////////////////////
/////////////////////////  INFORMATION ///////////////////////////
FStruct_CharacterStats AEnemies_Unit::GetEnemyStats()
{
	FStruct_CharacterStats enemyStats;
	enemyStats.Health = Current_Health;
	enemyStats.Attack = Current_Attack;
	enemyStats.Defense = Current_Defense;
	enemyStats.MagicAttack = Current_MagicAttack;
	enemyStats.MagicDefense = Current_MagicDefense;

	enemyStats.MaxHealth = Max_Health;

	enemyStats.Armor = Current_Armor;
	enemyStats.MaxArmor = Max_Armor;

	return enemyStats;
}
bool AEnemies_Unit::GetisEnemyDead(){ return isEnemyDead; }

FStruct_DeathData AEnemies_Unit::GetDeathData() 
{ 
	deathData.id = id;
	deathData.idWave = idWave;
	deathData.idZone = idZone;
	deathData.isDead = isEnemyDead;
	return deathData;
}
void AEnemies_Unit::SethasSendDeadMessage(bool hasSend) {  deathData.hasSendDeadMessage = hasSend; }
