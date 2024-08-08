// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SaveGameSlots/SG_OrdersSlot.h"
#include "Delegates/DelegateCombinations.h"
#include "SavebleSubsystemBase.h"
#include "OrdersSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewOrderDelegate, FOrder, NewOrder);

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UOrdersSubsystem : public USavebleSubsystemBase
{
	GENERATED_BODY()
	
public:
	void InitializeSubsystem(FString InSaveSlotName, UDataTable *ProductsDataTable, FTimerManager& TimerManger);

public:
	UFUNCTION(BlueprintCallable, Category = "OrderData")
	const TArray<FProduct>& GetProducts() const;

	UFUNCTION(BlueprintCallable, Category = "OrderData")
	TArray<FOrder>& GetCurrentOrders();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	TArray<FRestaurant> Restaurants;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	TArray<FDestination> Destinations;

private:
	UPROPERTY()
	TArray<FProduct> Products;

public:
	UFUNCTION(BlueprintCallable)
	FOrder SetCurrentOrder(int Id);

	UFUNCTION(BlueprintCallable)
	void SetCurrentOrderState(OrderState NewState);

	UFUNCTION(BlueprintCallable)
	FOrder& GetCurrentOrder();

	UFUNCTION(BlueprintCallable)
	void AddOrder();

	UPROPERTY(BlueprintAssignable)
	FNewOrderDelegate NewOrderDispatcher;

private:
	UPROPERTY()
	USG_OrdersSlot* OrdersSave;

	FTimerHandle OrdersTimerHandle;
};
