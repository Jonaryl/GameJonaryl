// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "List_PlayerClasses.h"

#include "PlayerF_Stats.generated.h"

UCLASS()
class APlayerF_Stats : public ACharacter
{
	GENERATED_BODY()

protected:
	APlayerF_Stats();

	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "Information", DisplayName = "Character name"))
		FString CharacterName;
							
	/////////////////////////// Basic stats ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
		float Base_Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
		float Base_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
		float Base_Defense;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
		float Base_MagicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
		float Base_MagicDefense;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics")
		float Base_Armor;


	/////////////////////////// Classe stats ///////////////////////////
	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "ClassList", DisplayName = "Character Class"))
		EList_PlayerClasses ClassCharacter;
	FString Classe;

	float Classe_Health;
	float Classe_Attack;
	float Classe_Defense;
	float Classe_MagicAttack;
	float Classe_MagicDefense;
	float Classe_SpeedMove;
	float Classe_SpeedRotate;

	float Classe_Armor;
	/////////////////////////// Maximum stats Value ///////////////////////////
	float Max_Health;
	float Max_Attack;
	float Max_Defense;
	float Max_MagicAttack;
	float Max_MagicDefense;
	float Max_SpeedMove;
	float Max_SpeedRotate;

	float Max_Armor;
	/////////////////////////// Current stats Value ///////////////////////////
	float Current_Health;
	float Current_Attack;
	float Current_Defense;
	float Current_MagicAttack;
	float Current_MagicDefense;
	float Current_SpeedMove;
	float Current_SpeedRotate;

	float Current_Armor;
	
	/////////////////////////// Special stats ///////////////////////////
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics Spe")
	//	float cutDamageStamina;
	//float currentCutDamageStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics Spe")
		float counterGaugeMax;
	float currentCounterGauge;

	virtual void BeginPlay() override;
	
	bool isSuperMode;
};
