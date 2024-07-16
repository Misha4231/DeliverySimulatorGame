// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProductsListEntry.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UProductsListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Title;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Quantity;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SumPrice;
};
