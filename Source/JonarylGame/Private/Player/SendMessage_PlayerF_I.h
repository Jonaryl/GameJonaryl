
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Structures/Struct_SendMessage.h"

#include "SendMessage_PlayerF_I.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USendMessage_PlayerF_I : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ISendMessage_PlayerF_I
{
	GENERATED_BODY()

public:
	/*
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Manager")
		void ManagerSendState(FStruct_SendMessage message);
};


