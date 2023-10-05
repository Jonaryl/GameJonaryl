// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_SpecialAttack.h"
#include "GameFramework/WorldSettings.h"

#include "PlayerFight_Character.h"
#include "Enemy_Unit.h"

#include "PlayerFight_SA_Jonaryl.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API UPlayerFight_SA_Jonaryl : public UPlayerFight_SpecialAttack
{
	GENERATED_BODY()


public:
	virtual void SpecialAttack() override;

	virtual void StartSlowMotion(float slowStrength) override;
	virtual void EndSlowMotion() override;
	

	virtual void XBtnActionSpe() override;
	virtual void YBtnActionSpe() override;
	virtual void BBtnActionSpe() override;
	virtual void ABtnActionSpe() override;

	virtual void GetPlayer(AActor* player) override;

private:
	APlayerFight_Character* PlayerFight_Character;


	////////////////////////////////////////// DEBUG //////////////////////////////////////////////////////
	virtual void RemoveAllEnemy() override;
	virtual void AllEnemyEndSlow() override;
};
