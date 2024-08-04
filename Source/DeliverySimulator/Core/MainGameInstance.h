// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DeliverySimulator/Core/SaveGameSlots/SG_OrdersSlot.h"
#include "DeliverySimulator/Checkpoints/DestinationCheckpoint.h"
#include "DeliverySimulator/Checkpoints/RestaurantCheckpoint.h"
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

	
	UFUNCTION(BlueprintCallable, Category = "OrderData")
	const TArray<FProduct>& GetProducts() const;

	UFUNCTION(BlueprintCallable, Category = "OrderData")
	const TArray<FOrder>& GetCurrentOrders() const;

	UFUNCTION(BlueprintCallable, Category = "OrderData")
	const int GetCurrentOrdersLength() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OrderData")
	UDataTable* ProductsDataTable;


	UFUNCTION(BlueprintCallable)
	FOrder SetCurrentOrder(int Id);

	UFUNCTION(BlueprintCallable)
	void CurrentOrderDone();

	UFUNCTION(BlueprintCallable)
	void CancelCurrentOrder();

	UFUNCTION(BlueprintCallable)
	FOrder& GetCurrentOrder();

	UFUNCTION(BlueprintCallable)
	void LoadOrdersSlotData();

	UFUNCTION(BlueprintCallable)
	void SaveOrdersSlotData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	TArray<FRestaurant> Restaurants;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	TArray<FDestination> Destinations;

	UFUNCTION(BlueprintCallable)
	void AddOrder();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	TArray<FProduct> Products;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	TArray<FOrder> Orders;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	FString OrdersSaveSlotName = "OrderSave";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrderData")
	USG_OrdersSlot* OrdersSave;

	FTimerHandle OrdersTimerHandle;
};
