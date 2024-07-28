// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderDetailsScreen.h"

void UOrderDetailsScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate)
{
}

void UOrderDetailsScreen::NativeConstruct()
{
    Restaurant->SetText(FText::FromString(OrderData->Order.Restaurant.Name));
    Destination->SetText(FText::FromString(OrderData->Order.Destination.Name));

    PercentFee->SetText(FText::FromString(
		FString::FormatAsNumber(OrderData->Order.PercentFee) + "%"
	));

	float OrderCost = 0;
	for (const FOrderProduct& Product : OrderData->Order.ProductList)
	{
		OrderCost += Product.Quantity * Product.Product.Price;

        UProductPassObject *ProductData = NewObject<UProductPassObject>(this);
        ProductData->Product = Product;
        
        ProductsListView->AddItem(ProductData);
    }

	float ClearEarnings = (OrderData->Order.PercentFee * OrderCost) / 100.f;
	float ClearEarningsRounded = FMath::RoundHalfToEven(ClearEarnings * 100.0f) / 100.0f;

	Earnings->SetText(FText::FromString(
		FString::SanitizeFloat(ClearEarningsRounded) + "$"
	));

    TakeOrderButton->OnClicked.AddDynamic(this, &UOrderDetailsScreen::TakeOrderButtonClicked);
}

void UOrderDetailsScreen::SetOrderData(URestaurantPassObject* InOrderData)
{
    OrderData = InOrderData;
}

void UOrderDetailsScreen::TakeOrderButtonClicked() {
    if (OrderData->OrdersScreenObject && OrderData->OnOrderTaken)
        (*OrderData->OrdersScreenObject.*OrderData->OnOrderTaken)(OrderData->Order.Id);
}