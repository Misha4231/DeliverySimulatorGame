// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreensRouting.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/GridPanel.h"
#include "DeliverySimulator/Core/MainGameInstance.h"
#include "OrdersScreen.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UOrdersScreen : public UUserWidget, public IScreenRoutingInterface
{
	GENERATED_BODY()

public:
	virtual void SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate);
protected:
	FScreenChangeDelegate ScreenChangeDelegate;
	FChangeToCreatedScreenDelegate ChangeToCreatedScreenDelegate;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta=(BindWidget))
	UListView* OrdersList;

	UPROPERTY(meta=(BindWidget))
	UBorder *OrdersListWrapper;

	UPROPERTY()
	UMainGameInstance* MainGameInstance;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OrderDetailsScreenClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OrdersScreenClass;

	UFUNCTION()
	void OnOrderTaken(int Id);

	UFUNCTION()
	void OnGoToDetails(URestaurantPassObject* SelectedOrder);

	UPROPERTY(meta=(BindWidget))
	UGridPanel *CurrentOrderWrapper;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *RestaurantTitle;

	UPROPERTY(meta=(BindWidget))
	UButton* DrawNavigationToRestaurantButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *DestinationTitle;

	UPROPERTY(meta=(BindWidget))
	UButton* DrawNavigationToDestinationButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *TotalEarnings;

private:
	int CurrentDisplayingTakenOrderId;
};
