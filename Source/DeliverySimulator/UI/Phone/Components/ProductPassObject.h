// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DeliverySimulator/Core/SaveGameSlots/SG_OrdersSlot.h"
#include "ProductPassObject.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UProductPassObject : public UObject
{
	GENERATED_BODY()

public:
	UProductPassObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOrderProduct Product;
};
