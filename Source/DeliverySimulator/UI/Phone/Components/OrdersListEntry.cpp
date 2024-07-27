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

		float OrderCost = 0;
		for (const FOrderProduct& Product : OrderData->Order.ProductList)
		{
			OrderCost += Product.Quantity * Product.Product.Price;
			// UProductPassObject* PassObject = NewObject<UProductPassObject>(this);
			// PassObject->Product = Product;

			// ProductsList->AddItem(PassObject);
		}

		float ClearEarnings = (OrderData->Order.PercentFee * OrderCost) / 100.f;
		float ClearEarningsRounded = FMath::RoundHalfToEven(ClearEarnings * 100.0f) / 100.0f;

		Earnings->SetText(FText::FromString(
			FString::SanitizeFloat(ClearEarningsRounded) + "$"
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
