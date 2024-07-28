// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreensRouting.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DeliverySimulator/UI/Phone/Components/RestaurantPassObject.h"
#include "DeliverySimulator/UI/Phone/Components/ProductPassObject.h"
#include "OrderDetailsScreen.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UOrderDetailsScreen : public UUserWidget, public IScreenRoutingInterface
{
	GENERATED_BODY()
	
public:
	virtual void SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate);

public:
	virtual void NativeConstruct() override;

private:
	URestaurantPassObject* OrderData;

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock *Restaurant;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *Destination;

	UPROPERTY(meta=(BindWidget))
	UListView* ProductsListView;

	UPROPERTY(meta=(BindWidget))
	UButton* TakeOrderButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Distance;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PercentFee;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Earnings;

	UFUNCTION()
	void SetOrderData(URestaurantPassObject* InOrderData);

	UFUNCTION()
	void TakeOrderButtonClicked();
};
