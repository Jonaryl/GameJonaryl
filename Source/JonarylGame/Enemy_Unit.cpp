// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Unit.h"

void AEnemy_Unit::BeginPlay()
{
	Super::BeginPlay();
	//CollisionDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionDamage = AEnemy_Unit::FindComponentByClass<UBoxComponent>();
	if (CollisionDamage)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionDamage ça marche enenemy"));

		CollisionDamage->SetupAttachment(RootComponent);

		CollisionDamage->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionDamage->SetCollisionObjectType(ECC_Pawn);
		CollisionDamage->SetCollisionResponseToAllChannels(ECR_Block);
		CollisionDamage->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	}
}


void AEnemy_Unit::EndAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("EndAnimation EndAnimation EndAnimation EndAnimation enemy"));
	hitCountDamageAnimation = 0;
	isDamaged = false;
}

float AEnemy_Unit::GetxMove()
{
	return Super::GetxMove();
}
float AEnemy_Unit::GetyMove()
{
	return Super::GetyMove();
}


bool AEnemy_Unit::GetisDamaged()
{
	return isDamaged;
}
bool AEnemy_Unit::GetisDamagedRight()
{
	return isRightAttackHit;
}
int AEnemy_Unit::GethitCountDamageAnimation()
{
	return hitCountDamageAnimation;
}

bool AEnemy_Unit::GetisAttacking()
{
	return Super::GetisAttacking();
}
bool AEnemy_Unit::GetisComboAttacking()
{
	return Super::GetisComboAttacking();
}
int AEnemy_Unit::GetcurrentCombo()
{
	return Super::GetcurrentCombo();
}


void AEnemy_Unit::CanAttack()
{
	return Super::CanAttack();
}
void AEnemy_Unit::ParticleLaunch()
{
	return Super::ParticleLaunch();
}
void AEnemy_Unit::DamageTake(int damage, bool isRightDamage)
{
	return Super::DamageTake(damage,isRightDamage);
}


void AEnemy_Unit::AttackIsRight()
{
	return Super::AttackIsRight();
}
void AEnemy_Unit::AttackIsLeft()
{
	return Super::AttackIsLeft();
}