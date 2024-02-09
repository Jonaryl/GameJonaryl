// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States_EnemiesActions.generated.h"

UCLASS()
class UStates_EnemiesActions : public UObject
{
    GENERATED_BODY()

public:
    enum class EStates_EnemiesActions
    {
        Idle,
        Walk,
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
        Slow,
        OnAir,
        OnGround,
        CounterPose,
        Counter,
        CounterAttack,
        Dead
    };
};
