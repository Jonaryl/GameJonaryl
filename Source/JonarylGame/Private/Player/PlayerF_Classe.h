// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerF_Stats.h"
#include "PlayerF_Classe.generated.h"

/**
 * 
 */
UCLASS()
class APlayerF_Classe : public APlayerF_Stats
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
