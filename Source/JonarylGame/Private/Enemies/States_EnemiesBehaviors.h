// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States_EnemiesBehaviors.generated.h"

UENUM()
enum EStates_EnemiesBehaviors
{
    WaitingNextAction,
    ChasingPlayer,
    AttackPlayer,
    CounterAttacking,
    DodgeAttack,
    SearchingPlayer,
    TurnAroundPlayer,
    EvaluatePlayer,
    IsInterrupted,
    Death
};

