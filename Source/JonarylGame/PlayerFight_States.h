// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerFight_States.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_States : public APlayerState
{
	GENERATED_BODY()
public:
    // Déclarez une énumération pour les différents états possibles de votre personnage
    enum class EPlayerFight_State
    {
        Idle,
        Run,
        Sprint,
        SuperRun,
        Jump,
        IdleJump,
        DashJump,
        Attack,
        StanceSpe,
        AttackSpe,
        Dash,
        Dodge,
        Damage,
        OnAir,
        OnGround,
        CounterPose,
        Counter,
        CounterAttack
    };

	
};
