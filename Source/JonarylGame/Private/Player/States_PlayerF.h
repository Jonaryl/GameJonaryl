// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "States_PlayerF.generated.h"

/**
 * 
 */
UCLASS()
class AStates_PlayerF : public APlayerState
{
	GENERATED_BODY()

public:
        enum class EStates_PlayerF
    {
        Idle,
        Run,
        Sprint,
        SuperRun,
        JumpUp,
        IdleJump,
        JumpDown,
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
        CounterAttack,
        EndAction
    };
};
