// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
// #include "DeliverySimulator/Core/SaveGameSlots/SG_OrdersSlot.h"
// #include "DeliverySimulator/Checkpoints/DestinationCheckpoint.h"
// #include "DeliverySimulator/Checkpoints/RestaurantCheckpoint.h"
#include "Subsystems/OrdersSubsystem.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Orders")
	UOrdersSubsystem *OrdersSubsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orders")
	UDataTable* ProductsDataTable;

};
