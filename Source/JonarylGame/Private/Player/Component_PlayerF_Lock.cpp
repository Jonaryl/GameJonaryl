// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component_PlayerF_Lock.h"

AActor* UComponent_PlayerF_Lock::GetLastTarget()
{
	return EnemyTarget;
}
void UComponent_PlayerF_Lock::EnemyDead()
{
	EnemyTarget = nullptr;
}

void UComponent_PlayerF_Lock::Update(FVector playerPosition, FVector playerNextPosition)
{
    float EnemyCheckDistance = -900.0f;
    float StartRaycastDistance = -100.0f;
    FVector PlayerLocation = playerPosition;
    FVector PointLocation = playerNextPosition;


    FVector DirectionRaycast = (PlayerLocation - PointLocation).GetSafeNormal();

    FVector StartLocation = PlayerLocation + StartRaycastDistance * DirectionRaycast;
    FVector EndLocation = PlayerLocation + EnemyCheckDistance * DirectionRaycast;

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;

    //DrawDebugLine(GetWorld(), StartLocation , EndLocation, FColor::Green, false, 0.1f, 0, 2.0f);
    bool detectEnemy = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldStatic, QueryParams);

    if (detectEnemy)
    {
        if (HitResult.GetActor() && HitResult.GetActor()->IsA(AActor::StaticClass()))
        {
            FString ActorClassName = HitResult.GetActor()->GetClass()->GetName();
            //if (!ActorClassName.StartsWith(TEXT("Bp_PlayerF")))
            if (ActorClassName.StartsWith(TEXT("Bp_Enemies")))
            {
                if (!EnemyTarget)
                {
                    EnemyTarget = HitResult.GetActor();
                }
                if (EnemyTarget != HitResult.GetActor())
                {
                    EnemyTarget = HitResult.GetActor();
                }
            }

            float DistanceToEnemy = HitResult.Distance;
            FVector EnemylocationTest = HitResult.GetActor()->GetActorLocation();
            FString PositionString = EnemylocationTest.ToString();
        }
    }
}

