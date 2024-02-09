// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerF_Classe.h"


void APlayerF_Classe::BeginPlay()
{
    Super::BeginPlay();
    FString MyString;

    ////////////////// Define classes stats //////////////////
    switch (ClassCharacter)
    {
    case EList_PlayerClasses::Option1:
        MyString = "Option 1 selected.";
        Classe = "Tank";
        Classe_Health = 100;
        Classe_Attack = 10;
        Classe_Defense = 40;
        Classe_MagicAttack = 5;
        Classe_MagicDefense = 30;
        Classe_SpeedMove = 5;
        Classe_SpeedRotate = 2;

        Classe_Armor = 200;
        break;
    case EList_PlayerClasses::Option2:
        MyString = "Option 2 selected.";
        Classe = "Striker";
        Classe_Health = 50;
        Classe_Attack = 40;
        Classe_Defense = 10;
        Classe_MagicAttack = 20;
        Classe_MagicDefense = 8;
        Classe_SpeedMove = 10;
        Classe_SpeedRotate = 8;

        Classe_Armor = 100;
        break;
    case EList_PlayerClasses::Option3:
        MyString = "Option 3 selected.";
        Classe = "Status";
        Classe_Health = 30;
        Classe_Attack = 15;
        Classe_Defense = 8;
        Classe_MagicAttack = 50;
        Classe_MagicDefense = 50;
        Classe_SpeedMove = 12;
        Classe_SpeedRotate = 10;

        Classe_Armor = 60;
        break;
    case EList_PlayerClasses::Option4:
        MyString = "Option 4 selected.";
        Classe = "Assassin";
        Classe_Health = 10;
        Classe_Attack = 80;
        Classe_Defense = 8;
        Classe_MagicAttack = 15;
        Classe_MagicDefense = 5;
        Classe_SpeedMove = 15;
        Classe_SpeedRotate = 12;

        Classe_Armor = 40;
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

        Classe_Armor = 1;
        break;
    }

    UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);

    ////////////////// Define base stats //////////////////
    Max_Health = Base_Health + Classe_Health;
    Max_Attack = Base_Attack + Classe_Attack;
    Max_Defense = Base_Defense + Classe_Defense;
    Max_MagicAttack = Base_MagicAttack + Classe_MagicAttack;
    Max_MagicDefense = Base_MagicDefense + Classe_MagicDefense;

    Max_Armor = Base_Armor + Classe_Armor;

    Current_Health = Base_Health + Classe_Health;
    Current_Attack = Base_Attack + Classe_Attack;
    Current_Defense = Base_Defense + Classe_Defense;
    Current_MagicAttack = Base_MagicAttack + Classe_MagicAttack;
    Current_MagicDefense = Base_MagicDefense + Classe_MagicDefense;

    Current_Armor = Base_Armor + Classe_Armor;
}