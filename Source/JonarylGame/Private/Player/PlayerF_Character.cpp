// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerF_Character.h"





////////////////////////////////////////////////////////////////
/////////////////////////  ANIMATION ///////////////////////////
/// EVENT ///
void APlayerF_Character::EventAnim()
{
	UE_LOG(LogTemp, Error, TEXT("EventAnim"));
}




/// METHOD
void APlayerF_Character::NeutralAction()
{
	canMove = true;
	canAttack = true;
	canBeHit = true;
	canSprint = true;
}

void APlayerF_Character::EndAllActionAnim()
{
	Super::EndAllActionAnim();

	isJumpUp = false;
	isJumpIdle = false;
	isJumpDown = false;
	isJumpDash = false;

	isDash = false;

	isDamaged = false;

	isAttacking = false;
	currentHitCombo = -1;

	isCounterPose = false;
	isCounter = false;
}
void APlayerF_Character::EndPartialAction()
{
	isJumpUp = false;
	isJumpIdle = false;
	isJumpDown = false;

	isDash = false;

	isDamaged = false;

	isAttacking = false;

	isCounterPose = false;
	isCounter = false;
}
void APlayerF_Character::StopMovingAnim()
{
	isMoving = false;
	isIdle = false;
	canMove = false;

	UE_LOG(LogTemp, Warning, TEXT(" StopMovingAnim isMoving = %s"), isMoving ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" StopMovingAnim isIdle = %s"), isIdle ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" StopMovingAnim  canMove = %s"), canMove ? TEXT("True") : TEXT("False"));
}


/// VARIABLE ///
//MOVE
bool APlayerF_Character::GetisIdle() { return isIdle; }
bool APlayerF_Character::GetisMoving() { return isMoving; }
bool APlayerF_Character::GetisSprint() { return isSprint; }

float APlayerF_Character::GetsideMoving() { return sideMoving; }

//JUMP
bool APlayerF_Character::GetisJumpUp() { return isJumpUp; }
bool APlayerF_Character::GetisJumpIdle() { return isJumpIdle; }
bool APlayerF_Character::GetisJumpDown() { return isJumpDown; }
bool APlayerF_Character::GetisJumpDash() { return isJumpDash; }

//DASH
bool APlayerF_Character::GetisDash() { return isDash; }

int APlayerF_Character::GetdashNumber() { return dashNumber; }

//DAMAGE
bool APlayerF_Character::GetisDamaged() { return isDamaged; }

//ATTACK
bool APlayerF_Character::GetisAttacking() { return isAttacking; }

int APlayerF_Character::GetcurrentHitCombo() { return currentHitCombo; }
int APlayerF_Character::GetAttackOneNumber() { return AttackOneNumber; }

//SEPCIAL
bool APlayerF_Character::GetisSuperMode() { return isSuperMode; }

bool APlayerF_Character::GetisSpeActionA() { return isSpeActionA; }
bool APlayerF_Character::GetisSpeActionB() { return isSpeActionB; }
bool APlayerF_Character::GetisSpeActionX() { return isSpeActionX; }
bool APlayerF_Character::GetisSpeActionY() { return isSpeActionY; }

//COUNTER
bool APlayerF_Character::GetisCounterPose() { return isCounterPose; }
bool APlayerF_Character::GetisCounter() { return isCounter; }
bool APlayerF_Character::GetisRightCounter() { return isRightCounter; }

int APlayerF_Character::GetcounterPoseNumber() { return counterPoseNumber; }
int APlayerF_Character::GetcounterNumber() { return counterNumber; }



/////////////////////////  ANIMATION ///////////////////////////
////////////////////////////////////////////////////////////////



