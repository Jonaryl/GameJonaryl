// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct_CharacterStats.generated.h"

USTRUCT(BlueprintType)
struct  JONARYLGAME_API FStruct_CharacterStats
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Attack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Defense;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MagicAttack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MagicDefense;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHealth;	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)

	float Armor;	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxArmor;
};
