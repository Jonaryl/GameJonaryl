// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SendMessage_PlayerF.h"


void ASendMessage_PlayerF::BeginPlay()
{
    Super::BeginPlay();
}
void ASendMessage_PlayerF::ManagerSendState_Implementation(FStruct_SendMessage message)
{
    UStates_PlayerF::EStates_PlayerF state = CheckState(message.CurrentState);

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScene_EnemiesManager::StaticClass(), FoundActors);
    for (AActor* Actor : FoundActors)
    {
        AScene_EnemiesManager* EnemyManager = Cast<AScene_EnemiesManager>(Actor);
        if (EnemyManager)
        {
            EnemyManager->SharePlayerState(state);
        }
        break;
    }
}

UStates_PlayerF::EStates_PlayerF ASendMessage_PlayerF::CheckState(FString playerStates)
{
    UStates_PlayerF::EStates_PlayerF state = UStates_PlayerF::EStates_PlayerF::Idle;

    if (playerStates == "Idle")
        state = UStates_PlayerF::EStates_PlayerF::Idle;
    else if (playerStates == "Run")
        state = UStates_PlayerF::EStates_PlayerF::Run;
    else if (playerStates == "Sprint")
        state = UStates_PlayerF::EStates_PlayerF::Sprint;
    else if (playerStates == "SuperRun")
        state = UStates_PlayerF::EStates_PlayerF::SuperRun;
    else if (playerStates == "JumpUp")
        state = UStates_PlayerF::EStates_PlayerF::JumpUp;
    else if (playerStates == "IdleJump")
        state = UStates_PlayerF::EStates_PlayerF::IdleJump;
    else if (playerStates == "JumpDown")
        state = UStates_PlayerF::EStates_PlayerF::JumpDown;
    else if (playerStates == "DashJump")
        state = UStates_PlayerF::EStates_PlayerF::DashJump;
    else if (playerStates == "Attack")
        state = UStates_PlayerF::EStates_PlayerF::Attack;
    else if (playerStates == "StanceSpe")
        state = UStates_PlayerF::EStates_PlayerF::StanceSpe;
    else if (playerStates == "AttackSpe")
        state = UStates_PlayerF::EStates_PlayerF::AttackSpe;
    else if (playerStates == "Dash")
        state = UStates_PlayerF::EStates_PlayerF::Dash;
    else if (playerStates == "Dodge")
        state = UStates_PlayerF::EStates_PlayerF::Dodge;
    else if (playerStates == "Damage")
        state = UStates_PlayerF::EStates_PlayerF::Damage;
    else if (playerStates == "OnAir")
        state = UStates_PlayerF::EStates_PlayerF::OnAir;
    else if (playerStates == "OnGround")
        state = UStates_PlayerF::EStates_PlayerF::OnGround;
    else if (playerStates == "CounterPose")
        state = UStates_PlayerF::EStates_PlayerF::CounterPose;
    else if (playerStates == "Counter")
        state = UStates_PlayerF::EStates_PlayerF::Counter;
    else if (playerStates == "CounterAttack")
        state = UStates_PlayerF::EStates_PlayerF::CounterAttack;
    else if (playerStates == "ChangeAction")
        state = UStates_PlayerF::EStates_PlayerF::ChangeAction;

    return state;
}

