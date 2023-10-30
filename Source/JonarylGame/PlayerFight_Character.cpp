// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Character.h"

void APlayerFight_Character::BeginPlay()
{
	Super::BeginPlay();
	//CollisionDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionDamage = APlayerFight_Character::FindComponentByClass<UBoxComponent>();
	if (CollisionDamage)
	{
		CollisionDamage->SetupAttachment(RootComponent);

		CollisionDamage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionDamage->SetCollisionObjectType(ECC_Pawn);
		CollisionDamage->SetCollisionResponseToAllChannels(ECR_Block);
		CollisionDamage->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	}
}

void APlayerFight_Character::SuperModeActivate()
{
	if (isSuperMode == true)
	{
		isSuperMode = false;
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
	}
	else
		isSuperMode = true;
}


void APlayerFight_Character::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut, AActor* Enemy)
{
	return Super::DamageTake(damage, isRightDamage, isCutFromDamage, damageCut, Enemy);
}

void APlayerFight_Character::HitCount()
{
	return Super::HitCount();
}

float APlayerFight_Character::GetSpeed()
{
	return Super::GetSpeed(); 
}


bool APlayerFight_Character::GetisStartJump()
{
	return Super::GetisStartJump();
}
bool APlayerFight_Character::GetisIdleJump()
{
	return Super::GetisIdleJump();
}
bool APlayerFight_Character::GetisDashJump()
{
	return Super::GetisDashJump();
}
bool APlayerFight_Character::GetisDash()
{
	return Super::GetisDash();
}
int APlayerFight_Character::GetdashNumber()
{
	return Super::GetdashNumber();
}
int APlayerFight_Character::GetcounterNumber()
{
	return counterNumber;
}

bool APlayerFight_Character::GetisSprint()
{
	return Super::GetisSprint();
}

bool APlayerFight_Character::GetisIdle()
{
	return Super::GetisIdle();
}
bool APlayerFight_Character::GetisNearGround()
{
	return Super::GetisNearGround();
}

bool APlayerFight_Character::GetisAttacking()
{
	return Super::GetisAttacking();
}
bool APlayerFight_Character::GetisStrongAttacking()
{
	return Super::GetisStrongAttacking();
}
int APlayerFight_Character::GetcurrentCombo()
{
	return Super::GetcurrentCombo();
}
int APlayerFight_Character::GetAttackOneNumber()
{
	return AttackOneNumber;
}

bool APlayerFight_Character::GetisCounterStance()
{
	return Super::GetisCounterStance();
}
bool APlayerFight_Character::GetisCounter()
{
	return Super::GetisCounter();
}
bool APlayerFight_Character::GetisCounterLeft()
{
	return Super::GetisCounterLeft();
}

bool APlayerFight_Character::GetisDamageRight()
{
	return Super::GetisDamageRight();
}
bool APlayerFight_Character::GetisDamaged()
{
	return Super::GetisDamaged();
}
bool APlayerFight_Character::GetCanMove()
{
	return Super::GetCanMove();
}
bool APlayerFight_Character::GetisMoving()
{
	return Super::GetisMoving();
}
bool APlayerFight_Character::GethasLanded()
{
	return Super::GethasLanded();
}


bool APlayerFight_Character::GetisSuperMode()
{
	return isSuperMode;
}
bool APlayerFight_Character::GetAttackSpeB()
{
	return AttackSpeB;
}
bool APlayerFight_Character::GetAttackSpeX()
{
	return AttackSpeX;
}
bool APlayerFight_Character::GetAttackSpeY()
{
	return AttackSpeY;
}
void APlayerFight_Character::SetAttackSpeY(bool speB, bool speX, bool speY)
{
	AttackSpeB = speB;
	AttackSpeX = speX;
	AttackSpeY = speY;
}



void APlayerFight_Character::CanAttack()
{
	if (currentCombo < comboLength)
		canAttack = true;

	if(CurrentState == APlayerFight_States::EPlayerFight_State::CounterPose)
		canAttack = true;

	currentAttack++;
	if (currentAttack == comboLength+1 && currentCombo != comboLength+1 || currentAttack == comboLength+2)
		currentAttack = 1;
}
void APlayerFight_Character::FinalComboAttack()
{
	canFinalComboAttack = false;
	canAttack = false;
}

void APlayerFight_Character::EndAttack()
{
	UE_LOG(LogTemp, Error, TEXT(" EndAttack "));
	if (loopTurn < 26 && CurrentState == APlayerFight_States::EPlayerFight_State::Dash || CurrentState == APlayerFight_States::EPlayerFight_State::Jump)
	{}
	else
	{
		if (isAttacking && !canMove && !canMoveWhenCombo && CurrentState == APlayerFight_States::EPlayerFight_State::Run)
		{}
		else
		{
			hasLanded = true;
			canMove = true;
			isAttacking = false;
			isStrongAttacking = false;
			isCounter = false;

			AttackSpeB = false;
			AttackSpeX = false;
			AttackSpeY = false;

			canStrongAttack = true;

			isStartJump = false;
			isIdleJump = false;
			isDashJump = false;
			isDash = false;
			canDash = true;

			if (CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Dash  
				|| CurrentState == APlayerFight_States::EPlayerFight_State::AttackSpe )
			{
				if (isMoveInput)
				{
					SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
					canAttack = true;
					RootMotionProblem = false;
					canStrongAttack = true;
					canCounterStance = true;
					canMoveWhenCombo = true;
				}
			}

				//canBeHit = true;
				//canBeHitCoolDown = 3;
				//canCounterStance = true;

			if (isSuperMode == false)
			{
				if (CurrentState == APlayerFight_States::EPlayerFight_State::Damage || CurrentState == APlayerFight_States::EPlayerFight_State::StanceSpe ||
					CurrentState == APlayerFight_States::EPlayerFight_State::CounterAttack ||
					CurrentState == APlayerFight_States::EPlayerFight_State::Counter || CurrentState == APlayerFight_States::EPlayerFight_State::CounterPose)
				{
					SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
					canAttack = true;
				}
			}
			else if (CurrentState == APlayerFight_States::EPlayerFight_State::CounterAttack)
				SetCharacterState(APlayerFight_States::EPlayerFight_State::StanceSpe, 0.0f);
		}

	}

}
void APlayerFight_Character::EndAnimation()
{
	UE_LOG(LogTemp, Error, TEXT(" EndAnimation "));
	isIdle = true;
	canCounterStance = true;
	isCounterStance = false;
	canAttack = true;
	isStrongAttacking = false;
	isCounter = false;

	AttackSpeB = false;
	AttackSpeX = false;
	AttackSpeY = false;

	RootMotionProblem = false;

	currentCombo = 0;
	currentAttack = 0;
	currentHit = 0;
	isAttacking = false;
	isStrongAttacking = false;
	canStrongAttack = true;

	canMoveWhenCombo = true;


	if (CurrentState == APlayerFight_States::EPlayerFight_State::Jump || CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump ||
		CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
	{
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
	}


	if (CurrentState == APlayerFight_States::EPlayerFight_State::Damage || CurrentState == APlayerFight_States::EPlayerFight_State::StanceSpe || 
		CurrentState == APlayerFight_States::EPlayerFight_State::AttackSpe ||	
		CurrentState == APlayerFight_States::EPlayerFight_State::Counter || CurrentState == APlayerFight_States::EPlayerFight_State::CounterPose)
	{
		if(isSuperMode == false)
			SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
	}
	//hasLanded = false;
}
void APlayerFight_Character::EndCombo()
{ ActionEndCombo(); }
void APlayerFight_Character::ActionEndCombo()
{
	if (currentCombo == currentAttack)
	{
		currentCombo = 0;
		currentAttack = 0;
		currentHit = 0;
		isAttacking = false;
		isStrongAttacking = false;
		canAttack = true;
	}

	if (isMoveInput == true)
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
	else
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
}


void APlayerFight_Character::EndCounterStance()
{ 
	EndCounterStanceMethod(); 
}
void APlayerFight_Character::EndCounterStanceMethod()
{
	isCounterStance = false;
}


void APlayerFight_Character::EndSlowEnemy()
{
	if (SpecialAttacknstance)
		SpecialAttacknstance->AllEnemyEndSlow();
	isSuperMode = false;
}


void APlayerFight_Character::CanCounterStance()
{ CanCounterStanceMethod(); 
}
void APlayerFight_Character::CanCounterStanceMethod()
{
	canCounterStance = true;
	if (isMoveInput == true)
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
	else
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
}
void APlayerFight_Character::ResetEvent()
{
	dashNumber = 0;
}
void APlayerFight_Character::ResetEventMethod()
{
	dashNumber = 0;

}


void APlayerFight_Character::EndCounter()
{
	isCounter = false;
}
void APlayerFight_Character::CanCounter()
{
	canCounter = true;
}