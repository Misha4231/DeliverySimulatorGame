// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/SaveGame.h"
#include "SavebleSubsystemBase.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API USavebleSubsystemBase : public UObject
{
	GENERATED_BODY()
	
private:
	FString SaveSlotName;
	TSubclassOf<USaveGame> SaveObjectType;

protected:
	void InitializeSavingSystem(FString InSaveSlotName, TSubclassOf<USaveGame> InSaveObjectType);

public:
	USavebleSubsystemBase(){};

	UFUNCTION(BlueprintCallable)
	USaveGame* LoadSlotData();

	UFUNCTION(BlueprintCallable)
	void SaveSlotData(USaveGame* SaveObject);
};
