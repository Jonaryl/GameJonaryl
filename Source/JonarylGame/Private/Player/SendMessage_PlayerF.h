
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Player/SendMessage_PlayerF_I.h"
#include "States_PlayerF.h"
#include "Scene/Scene_EnemiesManager.h"

#include "Structures/Struct_SendMessage.h"

#include "SendMessage_PlayerF.generated.h"

UCLASS()
class ASendMessage_PlayerF : public AActor, public ISendMessage_PlayerF_I
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ManagerSendState_Implementation(FStruct_SendMessage message) override;

	UStates_PlayerF::EStates_PlayerF CheckState(FString playerStates);
};
