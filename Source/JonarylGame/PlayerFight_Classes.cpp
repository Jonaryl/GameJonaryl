// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Classes.h"

APlayerFight_Classes::APlayerFight_Classes()
{
    FString MyString;

    switch (ClassCharacter)
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

    UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);

}