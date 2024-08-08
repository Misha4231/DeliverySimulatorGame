// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SG_StatsSlot.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API USG_StatsSlot : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Balance;
};
