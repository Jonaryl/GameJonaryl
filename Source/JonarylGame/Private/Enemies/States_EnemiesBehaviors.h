// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States_EnemiesBehaviors.generated.h"

UCLASS()
class UStates_EnemiesBehaviors : public UObject
{
    GENERATED_BODY()

public:
    enum class EStates_EnemiesBehaviors
    {
        WaitingNextAction,
        ChasingPlayer,
        AttackPlayer,
        CounterAttack,
        DodgeAttack,
        SearchingPlayer,
        TurnAroundPlayer,
        EvaluatePlayer,
        IsInterrupted,
        Dead
    };
};
