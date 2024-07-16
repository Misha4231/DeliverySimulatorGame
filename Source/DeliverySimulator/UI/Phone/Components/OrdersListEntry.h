// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
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

	UPROPERTY(meta=(BindWidget))
	UButton* TakeOrderButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Destination;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* RestaurantName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PercentFee;

	UPROPERTY(meta=(BindWidget))
	UButton* ProductsCollapseButton;

	UPROPERTY(meta=(BindWidget))
	UImage* CollapseIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CollapseOpenedIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CollapseCloseIcon;

	UPROPERTY(meta=(BindWidget))
	UListView* ProductsList;
};
