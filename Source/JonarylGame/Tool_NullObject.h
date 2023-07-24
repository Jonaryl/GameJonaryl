// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Tool_NullObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JONARYLGAME_API UTool_NullObject : public UObject
{
	GENERATED_BODY()

public:	
	UTool_NullObject();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object")
		FVector ObjectPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object")
		FRotator ObjectRotation;


protected:

public:	

		
};
