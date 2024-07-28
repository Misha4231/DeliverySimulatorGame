// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersListEntry.h"

#include "ProductPassObject.h"

void UOrdersListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OrderData = Cast<URestaurantPassObject>(ListItemObject);

	if (OrderData)
	{
		PercentFee->SetText(FText::FromString(
			FString::FormatAsNumber(OrderData->Order.PercentFee) + "%"
		));

		Earnings->SetText(FText::FromString(
			FString::SanitizeFloat(OrderData->Order.CalculateEarnings()) + "$"
		));
	}
}

void UOrdersListEntry::NativeConstruct()
{
	Super::NativeConstruct();

	GoToDetailsButton->OnClicked.AddDynamic(this, &UOrdersListEntry::GoToDetails);
}

void UOrdersListEntry::GoToDetails()
{
	if (OrderData && OrderData->OrdersScreenObject) {
		(*OrderData->OrdersScreenObject.*OrderData->OnGoToDetails)(OrderData);
	}
}
