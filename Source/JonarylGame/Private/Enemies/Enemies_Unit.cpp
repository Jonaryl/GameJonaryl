// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Unit.h"

////////////////////////////////////////////////////////////////
/////////////////////////  ANIMATION ///////////////////////////
/// EVENT ///


/// METHOD
void AEnemies_Unit::StopAllActions()
{ 
	isIdle = false;
	isMoving = false;
	xyMovingValue = FVector(0, 0, 0);

	isDash = false;

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

/*
//COUNTER
bool AEnemies_Unit::GetisCounterPose() { return isCounterPose; }
bool AEnemies_Unit::GetisCounter() { return isCounter; }

//DAMAGE
bool AEnemies_Unit::GetisDamaged() { return isDamaged; }
bool AEnemies_Unit::GetisRightAttackHit() { return isRightAttackHit; }

float AEnemies_Unit::GetDmgBlendAlpha() { return DmgBlendAlpha; }
float AEnemies_Unit::GetDmgBlendR() { return DmgBlendR; }
float AEnemies_Unit::GetDmgBlendL() { return DmgBlendL; }

bool AEnemies_Unit::GetisSlowDownTake() { return isSlowDownTake; }
*/
