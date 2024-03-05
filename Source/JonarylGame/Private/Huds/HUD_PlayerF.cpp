// Fill out your copyright notice in the Description page of Project Settings.


#include "Huds/HUD_PlayerF.h"


void UHUD_PlayerF::SetHealth(float maxHealth, float currentHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(currentHealth / maxHealth);
}

void UHUD_PlayerF::SetClassPower(float maxClassPower, float currentClassPower)
{
	if (ClassPowerBar)
		ClassPowerBar->SetPercent(currentClassPower / maxClassPower);
}


void UHUD_PlayerF::SetVisible(bool isVisible)
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