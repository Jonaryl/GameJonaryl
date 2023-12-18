// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Lock.h"

// Sets default values for this component's properties
UPlayerFight_Lock::UPlayerFight_Lock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFight_Lock::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerFight_Lock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    
}


void UPlayerFight_Lock::GetPlayerPosRot(FVector playerPos, FRotator playerRot, AActor* player, FVector frontVector)
{
    playerPosition = playerPos;
    playerRotation = playerRot;
    PlayerFrom = player;
    playerFrontVector = frontVector;

    FString PositionString = playerPosition.ToString();
    //UE_LOG(LogTemp, Warning, TEXT("PositionString: %s"), *PositionString);
    FString PosString = playerPos.ToString();
    //UE_LOG(LogTemp, Warning, TEXT("PosString: %s"), *PosString);
    FString RotationString = playerRotation.ToString();
    //UE_LOG(LogTemp, Warning, TEXT("RotationString: %s"), *RotationString);
    FString RotString = playerRot.ToString();
    //UE_LOG(LogTemp, Warning, TEXT("RotString: %s"), *RotString);

}



void UPlayerFight_Lock::Update()
{
    //UE_LOG(LogTemp, Warning, TEXT("Update"));

    float EnemyCheckDistance = -900.0f;
    float StartRaycastDistance = -100.0f;
    FVector PlayerLocation = PlayerFrom->GetTargetLocation();
    FVector PointLocation = playerPosition;


    FVector DirectionRaycast = (PlayerLocation - PointLocation).GetSafeNormal(); 

    FVector StartLocation = PlayerLocation + StartRaycastDistance * DirectionRaycast; 
    FVector EndLocation = PlayerLocation + EnemyCheckDistance * DirectionRaycast;

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    //QueryParams.AddIgnoredActor(PlayerFrom);

    //DrawDebugLine(GetWorld(), StartLocation , EndLocation, FColor::Green, false, 0.1f, 0, 2.0f);
    bool detectEnemy = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("YOU HIT THE THING : %s"), *HitResult.GetActor()->GetName()));
    //UE_LOG(LogTemp, Warning, TEXT(" detectEnemy = %s"), *HitResult.GetActor()->GetName());

    if (detectEnemy)
    {
        if (HitResult.GetActor() && HitResult.GetActor()->IsA(AActor::StaticClass()))
        {
            FString ActorClassName = HitResult.GetActor()->GetClass()->GetName();
            if (!ActorClassName.StartsWith(TEXT("Bp_PlayerFigth")))
            {
                //UE_LOG(LogTemp, Warning, TEXT("ActorClassName %s"), *ActorClassName);
                if (!EnemyTarget)
                {
                    //UE_LOG(LogTemp, Warning, TEXT("EnemyTarget est bien null"));
                    EnemyTarget = HitResult.GetActor();
                }
                if (EnemyTarget != HitResult.GetActor())
                {
                    //UE_LOG(LogTemp, Warning, TEXT("EnemyTarget est bien diferrent d'avant"));
                    EnemyTarget = HitResult.GetActor();
                }
            }

            //UE_LOG(LogTemp, Warning, TEXT(" detectEnemy = %s"), detectEnemy ? TEXT("True") : TEXT("False"));
            float DistanceToEnemy = HitResult.Distance;
            FVector EnemylocationTest = HitResult.GetActor()->GetActorLocation();
            FString PositionString = EnemylocationTest.ToString();
        }
    }
    // ...
}

void UPlayerFight_Lock::Test( )
{
	UE_LOG(LogTemp, Warning, TEXT("Test Test Test v Test Test Test"));
	// ...
}

AActor* UPlayerFight_Lock::GetLastTarget()
{
	return EnemyTarget;
}

