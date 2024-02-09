// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct_DeathData.generated.h"

USTRUCT(BlueprintType)
struct  JONARYLGAME_API FStruct_DeathData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 idZone;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 idWave;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isDead;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool hasSendDeadMessage;
};
