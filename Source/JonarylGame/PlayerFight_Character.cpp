// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Character.h"

void APlayerFight_Character::BeginPlay()
{
	Super::BeginPlay();
	//CollisionDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionDamage = APlayerFight_Character::FindComponentByClass<UBoxComponent>();
	if (CollisionDamage)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionDamage ça marche"));

		CollisionDamage->SetupAttachment(RootComponent);

		CollisionDamage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionDamage->SetCollisionObjectType(ECC_Pawn);
		CollisionDamage->SetCollisionResponseToAllChannels(ECR_Block);
		CollisionDamage->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	}
}

void APlayerFight_Character::DamageTake(int damage, bool isRightDamage)
{
	return Super::DamageTake(damage, isRightDamage);
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



void APlayerFight_Character::CanAttack()
{
	if (currentCombo < 5 || currentCombo == 5 && isStrongAttacking == false)
		canAttack = true;

	currentAttack++;
	if (currentAttack == 6 && currentCombo != 6 || currentAttack == 7)
		currentAttack = 1;

	UE_LOG(LogTemp, Warning, TEXT(" CanAttack canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT("CanAttack currentCombo %d"), currentCombo);
	UE_LOG(LogTemp, Warning, TEXT("CanAttack currentAttack %d"), currentAttack);
}
void APlayerFight_Character::FinalComboAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("FinalComboAttack"));
	canFinalComboAttack = false;
	canAttack = false;
}

void APlayerFight_Character::EndCombo()
{ ActionEndCombo(); }
void APlayerFight_Character::ActionEndCombo()
{
	UE_LOG(LogTemp, Warning, TEXT("EndCombo"));
	UE_LOG(LogTemp, Warning, TEXT("EndAttackAnimationEvent currentCombo %d"), currentCombo);
	UE_LOG(LogTemp, Warning, TEXT("EndAttackAnimationEvent currentAttack %d"), currentAttack);

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
	//EndCounterStanceMethod(); 
}
void APlayerFight_Character::EndCounterStanceMethod()
{
	isCounterStance = false;
	UE_LOG(LogTemp, Warning, TEXT(" EndCounterStance isCounterStance = %s"), isCounterStance ? TEXT("True") : TEXT("False"));
}


void APlayerFight_Character::CanCounterStance()
{ //CanCounterStanceMethod(); 
}
void APlayerFight_Character::CanCounterStanceMethod()
{
	canCounterStance = true;
	UE_LOG(LogTemp, Warning, TEXT(" CanCounterStance canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False"));
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