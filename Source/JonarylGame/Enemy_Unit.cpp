// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Unit.h"

float AEnemy_Unit::GetxMove()
{
	return Super::GetxMove();
}
float AEnemy_Unit::GetyMove()
{
	return Super::GetyMove();
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