// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_HUD.h"


void UPlayerFight_HUD::SetHealth(float maxHealth, float currentHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(currentHealth / maxHealth);
}

void UPlayerFight_HUD::SetClassPower(float maxClassPower, float currentClassPower)
{
	if (ClassPowerBar)
		ClassPowerBar->SetPercent(currentClassPower / maxClassPower);
}


void UPlayerFight_HUD::SetVisible(bool isVisible)
{
	if (isVisible)
	{
		if (HealthBar)
			HealthBar->SetVisibility(ESlateVisibility::Visible);
		if (ClassPowerBar)
			ClassPowerBar->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if (HealthBar)
			HealthBar->SetVisibility(ESlateVisibility::Hidden);
		if (ClassPowerBar)
			ClassPowerBar->SetVisibility(ESlateVisibility::Hidden);
	}
	
}