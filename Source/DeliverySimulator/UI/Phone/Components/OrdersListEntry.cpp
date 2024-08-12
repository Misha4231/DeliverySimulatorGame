// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersListEntry.h"
#include "ProductPassObject.h"
#include "../Screens/Orders/OrderDetailsScreen.h"

void UOrdersListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OrderData = Cast<UOrderPassObject>(ListItemObject);

	if (OrderData)
	{
		PercentFee->SetText(FText::FromString(
			FString::FormatAsNumber(OrderData->Order.PercentFee) + "%"
		));

		Earnings->SetText(FText::FromString(
			OrderData->Order.CalculateEarningsString() + "$"
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
	if (UOrderDetailsScreen *OrderDetailsScreenWidget = Cast<UOrderDetailsScreen>(CreateWidget<UUserWidget>(this, OrderDetailsScreenClass))) {
		OrderDetailsScreenWidget->SetOrderData(OrderData);

		if (OrderData->ChangeToCreatedScreenDelegate->IsBound()) {
			OrderData->ChangeToCreatedScreenDelegate->Execute(OrderDetailsScreenWidget);
		}
	}
}
