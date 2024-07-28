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

	for (const FOrderProduct& Product : OrderData->Order.ProductList)
	{
        UProductPassObject *ProductData = NewObject<UProductPassObject>(this);
        ProductData->Product = Product;
        
        ProductsListView->AddItem(ProductData);
    }
    
    Earnings->SetText(FText::FromString(
		OrderData->Order.CalculateEarnings() + "$"
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