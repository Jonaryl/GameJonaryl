// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Structures/Struct_CharacterStats.h"
#include "Structures/Struct_HitStats.h"

#include "Particle_Enemies_I.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UParticle_Enemies_I : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IParticle_Enemies_I
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
		void SetAttack(FStruct_CharacterStats enemyStats, FStruct_HitStats hitStats, AActor* currentEnemy);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Counter")
		void IsCountered(AActor* playerCountered);
};
