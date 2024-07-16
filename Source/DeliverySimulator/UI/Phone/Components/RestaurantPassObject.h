// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DeliverySimulator/Core/SG_OrdersSlot.h>

#include "RestaurantPassObject.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API URestaurantPassObject : public UObject
{
	GENERATED_BODY()

public:
	URestaurantPassObject();
	URestaurantPassObject(FRestaurant& InRestaurant);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRestaurant Restaurant;
};
