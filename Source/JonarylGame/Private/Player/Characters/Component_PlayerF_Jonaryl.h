// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Component_PlayerF_SpeAtk.h"


#include "Player/PlayerF_Character.h"
#include "../../../Enemy_Unit.h"

#include "Component_PlayerF_Jonaryl.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UComponent_PlayerF_Jonaryl : public UComponent_PlayerF_SpeAtk
{
	GENERATED_BODY()

public:
	/////////////////////////// START ///////////////////////////
	virtual void SpecialAttack(bool launchParticle) override;
	virtual void EndSpecialAttack() override;

	/////////////////////////// SLOW MOTION ///////////////////////////
	virtual void StartSlowMotion(float slowStrength) override;
	virtual void EndSlowMotion() override;
	virtual void AllEnemyEndSlow() override;

	/////////////////////////// INPUT ///////////////////////////
	virtual void XBtnActionSpe() override;
	virtual void YBtnActionSpe() override;
	virtual void BBtnActionSpe() override;
	virtual void ABtnActionSpe() override;


	/////////////////////////// TOOL ///////////////////////////
	virtual void GetPlayer(AActor* player) override;


protected:
	APlayerF_Character* currentPlayer;
	
};
