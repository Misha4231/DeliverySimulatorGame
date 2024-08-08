// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../SaveGameSlots/SG_StatsSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Delegates/DelegateCombinations.h"
#include "SavebleSubsystemBase.h"
#include "StatsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBalanceUpdateDispatcher, float, NewBalance);


/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UStatsSubsystem : public USavebleSubsystemBase
{
	GENERATED_BODY()
	
public:
	void InitializeSubsystem(FString SaveSlotName);

public: // balance functionality
	UFUNCTION(BlueprintCallable)
	float GetBalance();

	UFUNCTION(BlueprintCallable)
	void GiveMoney(float Amount);

public: // events
	UPROPERTY(BlueprintAssignable)
	FBalanceUpdateDispatcher BalanceDispatcher;

private:
	UPROPERTY()
	USG_StatsSlot *StatsSave;
};
