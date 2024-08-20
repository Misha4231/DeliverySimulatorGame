// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "OrderPassObject.h"
#include "../Screens/Base/PhoneScreen.h"
#include "OrdersListEntry.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UOrdersListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite)
	UOrderPassObject* OrderData;
	
	UPROPERTY(meta=(BindWidget))
	UButton* GoToDetailsButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Earnings;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* RestaurantName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DestinationName;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox *ProductsVisualizationWrapper;

	UPROPERTY(meta=(BindWidget))
	UImage *Logo;

	UFUNCTION()
	void GoToDetails();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPhoneScreen> OrderDetailsScreenClass;
};
