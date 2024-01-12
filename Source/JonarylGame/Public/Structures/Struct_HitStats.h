// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct_HitStats.generated.h"

USTRUCT(BlueprintType)
struct  JONARYLGAME_API FStruct_HitStats
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ArmorDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isRightDamage;
};
