// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "HUD_PlayerF.generated.h"

/**
 * 
 */
UCLASS()
class UHUD_PlayerF : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetHealth(float maxHealth, float currentHealth);
	void SetClassPower(float maxClassPower, float currentClassPower);

	void SetVisible(bool isVisible);


	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* ClassPowerBar;
};
