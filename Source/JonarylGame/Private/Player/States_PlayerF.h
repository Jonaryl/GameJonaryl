// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States_PlayerF.generated.h"

 
UCLASS()
class UStates_PlayerF : public UObject
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
        MoveSpe,
        AttackSpe,
        Dash,
        Dodge,
        Damage,
        OnAir,
        OnGround,
        CounterPose,
        Counter,
        CounterAttack,
        ChangeAction,
        Dead
    };
};
