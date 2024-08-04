// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DeliverySimulator/Core/SaveGameSlots/SG_OrdersSlot.h"
#include "Kismet/GameplayStatics.h"
#include <DeliverySimulator/Checkpoints/RestaurantCheckpoint.h>
#include <DeliverySimulator/Checkpoints/DestinationCheckpoint.h>
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrderData")
	TSubclassOf<ARestaurantCheckpoint> RestaurantCheckpointClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrderData")
	TSubclassOf<ADestinationCheckpoint> DestinationCheckpointClass;
};
