// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Character.h"





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


bool APlayerFight_Character::GetisIdle()
{
	return Super::GetisIdle();
}
bool APlayerFight_Character::GetisNearGround()
{
	return Super::GetisNearGround();
}