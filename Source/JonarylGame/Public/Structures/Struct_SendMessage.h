// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Struct_SendMessage.generated.h"


USTRUCT(BlueprintType)
struct  JONARYLGAME_API FStruct_SendMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString CurrentState;
};
