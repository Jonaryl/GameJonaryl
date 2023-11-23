// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharactertestroot.h"

// Sets default values
AMyCharactertestroot::AMyCharactertestroot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    FString MyString;

    switch (ClassEnemy)
    {
    case EClassList::Option1:
        MyString = "Option 1 selected.";
        Classe = "Tank";
        Classe_Health = 100;
        Classe_Attack = 10;
        Classe_Defense = 40;
        Classe_MagicAttack = 5;
        Classe_MagicDefense = 30;
        Classe_SpeedMove = 5;
        Classe_SpeedRotate = 2;
        break;
    case EClassList::Option2:
        MyString = "Option 2 selected.";
        Classe = "Striker";
        Classe_Health = 50;
        Classe_Attack = 40;
        Classe_Defense = 10;
        Classe_MagicAttack = 20;
        Classe_MagicDefense = 8;
        Classe_SpeedMove = 10;
        Classe_SpeedRotate = 8;
        break;
    case EClassList::Option3:
        MyString = "Option 3 selected.";
        Classe = "Status";
        Classe_Health = 30;
        Classe_Attack = 15;
        Classe_Defense = 8;
        Classe_MagicAttack = 50;
        Classe_MagicDefense = 50;
        Classe_SpeedMove = 12;
        Classe_SpeedRotate = 10;
        break;
    case EClassList::Option4:
        MyString = "Option 4 selected.";
        Classe = "Assassin";
        Classe_Health = 10;
        Classe_Attack = 80;
        Classe_Defense = 8;
        Classe_MagicAttack = 15;
        Classe_MagicDefense = 5;
        Classe_SpeedMove = 15;
        Classe_SpeedRotate = 12;
        break;
    default:
        MyString = "Invalid option selected.";
        Classe = "None";
        Classe_Health = 1;
        Classe_Attack = 1;
        Classe_Defense = 1;
        Classe_MagicAttack = 1;
        Classe_MagicDefense = 1;
        Classe_SpeedMove = 1;
        Classe_SpeedRotate = 1;
        break;
    }

    //UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);
}

// Called when the game starts or when spawned
void AMyCharactertestroot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharactertestroot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharactertestroot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

