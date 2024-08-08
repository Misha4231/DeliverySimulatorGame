// Fill out your copyright notice in the Description page of Project Settings.


#include "SavebleSubsystemBase.h"
#include "Kismet/GameplayStatics.h"

void USavebleSubsystemBase::InitializeSavingSystem(FString InSaveSlotName, TSubclassOf<USaveGame> InSaveObjectType)
{
    SaveSlotName = InSaveSlotName;
    SaveObjectType = InSaveObjectType;
}

USaveGame* USavebleSubsystemBase::LoadSlotData()
{
    if(UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		return UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	} else
	{
		USaveGame *SaveObject = UGameplayStatics::CreateSaveGameObject(SaveObjectType);
		UGameplayStatics::SaveGameToSlot(SaveObject, SaveSlotName, 0);
        return SaveObject;
    }
}

void USavebleSubsystemBase::SaveSlotData(USaveGame* SaveObject)
{
    if(UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		UGameplayStatics::SaveGameToSlot(SaveObject, SaveSlotName, 0);
		
	}
}
