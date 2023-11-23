// Fill out your copyright notice in the Description page of Project Settings.


#include "AMyCharactertestroot_Unit.h"


void AAMyCharactertestroot_Unit::BeginPlay()
{
	Super::BeginPlay();
	//CollisionDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionDamage = AAMyCharactertestroot_Unit::FindComponentByClass<UBoxComponent>();
	if (CollisionDamage)
	{
		CollisionDamage->SetupAttachment(RootComponent);

		CollisionDamage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionDamage->SetCollisionObjectType(ECC_Pawn);
		CollisionDamage->SetCollisionResponseToAllChannels(ECR_Block);
		CollisionDamage->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	}
}


void AAMyCharactertestroot_Unit::ActivateSlowMode()
{
	Super::ActivateSlowMode();
}
void AAMyCharactertestroot_Unit::EndSlowMode()
{
	Super::EndSlowMode();
}

void AAMyCharactertestroot_Unit::EndDamage()
{
	Super::EndDamage();
}
void AAMyCharactertestroot_Unit::EndDamageAnimation()
{
	Super::EndDamageAnimation();
}
void AAMyCharactertestroot_Unit::EndAnimation()
{
	hitCountDamageAnimation = 0;
	isDamaged = false;
	isSlowDownTake = false;
	EndDamageAnimation();
}

float AAMyCharactertestroot_Unit::GetxMove()
{
	return Super::GetxMove();
}
float AAMyCharactertestroot_Unit::GetyMove()
{
	return Super::GetyMove();
}


bool AAMyCharactertestroot_Unit::GetisDamaged()
{
	return isDamaged;
}
bool AAMyCharactertestroot_Unit::GetisDamagedRight()
{
	return isRightAttackHit;
}
int AAMyCharactertestroot_Unit::GethitCountDamageAnimation()
{
	return hitCountDamageAnimation;
}
bool AAMyCharactertestroot_Unit::GetisCounterTake()
{
	return isCounterTake;
}

bool AAMyCharactertestroot_Unit::GetisAttacking()
{
	return Super::GetisAttacking();
}
bool AAMyCharactertestroot_Unit::GetisComboAttacking()
{
	return Super::GetisComboAttacking();
}
int AAMyCharactertestroot_Unit::GetcurrentCombo()
{
	return Super::GetcurrentCombo();
}

float AAMyCharactertestroot_Unit::GetDmgBlendAlpha()
{
	return Super::GetDmgBlendAlpha();
}
float AAMyCharactertestroot_Unit::GetDmgBlendR()
{
	return Super::GetDmgBlendR();
}
float AAMyCharactertestroot_Unit::GetDmgBlendL()
{
	return Super::GetDmgBlendL();
}

bool AAMyCharactertestroot_Unit::GetisSlowDownTake()
{
	return Super::GetisSlowDownTake();
}


void AAMyCharactertestroot_Unit::CanAttack()
{
	return Super::CanAttack();
}
void AAMyCharactertestroot_Unit::ParticleLaunch()
{
	return Super::ParticleLaunch();
}
void AAMyCharactertestroot_Unit::DamageTake(int damage, bool isRightDamage)
{
	return Super::DamageTake(damage, isRightDamage);
}
void AAMyCharactertestroot_Unit::CounterTake()
{
	return Super::CounterTake();
}
void AAMyCharactertestroot_Unit::SlowDownTake()
{
	return Super::SlowDownTake();
}
void AAMyCharactertestroot_Unit::ModifyDmgBlend(float alpha, float alphaR, float alphaL)
{
	return Super::ModifyDmgBlend(alpha, alphaR, alphaL);
}


void AAMyCharactertestroot_Unit::AttackIsRight()
{
	return Super::AttackIsRight();
}
void AAMyCharactertestroot_Unit::AttackIsLeft()
{
	return Super::AttackIsLeft();
}
