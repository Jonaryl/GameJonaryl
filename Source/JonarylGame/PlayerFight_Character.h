// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Actions.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerFight_Character.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Character : public APlayerFight_Actions
{
	GENERATED_BODY()

public:
	float GetSpeed() override;
	bool GetisStartJump() override;
	bool GetisIdleJump() override;
	bool GetisDashJump() override;
	bool GetisIdle() override;
	bool GetisNearGround() override;
	
};
