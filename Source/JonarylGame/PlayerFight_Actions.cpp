// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Actions.h"

APlayerFight_Actions::APlayerFight_Actions()
{
    PrimaryActorTick.bCanEverTick = true;

}

void APlayerFight_Actions::BeginPlay()
{
    Super::BeginPlay();

    // Initialisez le contrôleur de personnage

}

// Called every frame
void APlayerFight_Actions::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void APlayerFight_Actions::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("ABtn", IE_Pressed, this, &APlayerFight_Actions::AButton);

    PlayerInputComponent->BindAction("Bbtn", IE_Pressed, this, &APlayerFight_Actions::BButton);

    PlayerInputComponent->BindAction("Xbtn", IE_Pressed, this, &APlayerFight_Actions::XButton);

    PlayerInputComponent->BindAction("Ybtn", IE_Pressed, this, &APlayerFight_Actions::YButton);
}

void APlayerFight_Actions::AButton()
{
    UE_LOG(LogTemp, Warning, TEXT("A button pressed with value %f"), "value");
}
void APlayerFight_Actions::BButton()
{
    UE_LOG(LogTemp, Warning, TEXT("B button pressed with value %f"), "value");
}
void APlayerFight_Actions::XButton()
{
    UE_LOG(LogTemp, Warning, TEXT("X button pressed with value %f"), "value");
}
void APlayerFight_Actions::YButton()
{
    UE_LOG(LogTemp, Warning, TEXT("Y button pressed with value %f"), "value");
}