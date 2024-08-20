// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/PhoneScreen.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanel.h"
#include "DeliverySimulator/Core/MainGameInstance.h"
#include "../../Components/OrderPassObject.h"
#include "../../../Widgets/Buttons/ButtonWidget.h"
#include "OrdersScreen.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UOrdersScreen : public UPhoneScreen
{
	GENERATED_BODY()

public:
	virtual void ScreenConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UListView* OrdersList;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel *OrdersListWrapper;

	UPROPERTY(meta=(BindWidget))
	UButtonWidget *DetailsButton;

	UPROPERTY()
	UMainGameInstance* MainGameInstance;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OrderDetailsScreenClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OrdersScreenClass;




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

	UFUNCTION()
	void OnAddOrderToList(FOrder NewOrder);
};
