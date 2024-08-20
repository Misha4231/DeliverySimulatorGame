// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SG_OrdersSlot.generated.h"

USTRUCT(BlueprintType)
struct FRestaurant : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> AvailableFoodIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D *Logo;
};


USTRUCT(BlueprintType)
struct FDestination : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
};

USTRUCT(BlueprintType)
struct FProduct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D *Image;
};

USTRUCT(BlueprintType)
struct FOrderProduct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FProduct Product;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
};

UENUM()
enum OrderState
{
	NotTaken UMETA(DisplayName = "Not Taken"),
	OrderTaken UMETA(DisplayName = "Taken"),
	PoductsTaken UMETA(DisplayName = "Poducts Taken")
};

USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRestaurant Restaurant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDestination Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FOrderProduct> ProductList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PercentFee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<OrderState> State;

	float CalculateEarningsFloat();
	FString CalculateEarningsString();
};

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API USG_OrdersSlot : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FOrder> CurrentOrders;

	UFUNCTION(BlueprintCallable)
	FOrder AddOrder(TArray<FRestaurant>& AvailableRestaurants, TArray<FProduct>& AvailableProducts, TArray<FDestination>& AvailableDestinations);

	UFUNCTION(BlueprintCallable)
	void RemoveOrder(FOrder& Order);

	UPROPERTY(BlueprintReadWrite)
	FOrder CurrentOrderDelivering;

	UFUNCTION(BlueprintCallable)
	FOrder SetCurrentOrderDelivering(int Id);

	UFUNCTION(BlueprintCallable)
	void CancelCurrentOrderDelivering();
};
