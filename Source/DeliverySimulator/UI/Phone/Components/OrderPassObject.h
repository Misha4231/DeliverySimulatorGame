// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeliverySimulator/Core/SaveGameSlots/SG_OrdersSlot.h"
#include "../Screens/Base/PhoneScreen.h"
#include "OrderPassObject.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UOrderPassObject : public UObject
{
	GENERATED_BODY()

public:
	UOrderPassObject() 
		: ScreenChangeDelegate(nullptr), ChangeToCreatedScreenDelegate(nullptr) {}

	UOrderPassObject(FScreenChangeDelegate* InScreenChangeDelegate, FChangeToCreatedScreenDelegate* InChangeToCreatedScreenDelegate)
		: ScreenChangeDelegate(InScreenChangeDelegate), ChangeToCreatedScreenDelegate(InChangeToCreatedScreenDelegate)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOrder Order;

	FScreenChangeDelegate* ScreenChangeDelegate;
	FChangeToCreatedScreenDelegate* ChangeToCreatedScreenDelegate;
};