// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <DeliverySimulator/Core/SG_OrdersSlot.h>
#include <DeliverySimulator/UI/Phone/Screens/OrdersScreen.h>
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOrder Order;

	UPROPERTY()
	UOrdersScreen* OrdersScreenObject;
	void (UOrdersScreen::*OnOrderTaken)(int);
	void (UOrdersScreen::*OnGoToDetails)(URestaurantPassObject*);
};
