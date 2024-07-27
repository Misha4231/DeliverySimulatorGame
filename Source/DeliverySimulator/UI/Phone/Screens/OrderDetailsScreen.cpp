// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderDetailsScreen.h"

void UOrderDetailsScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate)
{
}

void UOrderDetailsScreen::NativeConstruct()
{
}

void UOrderDetailsScreen::SetOrderData(URestaurantPassObject* InOrderData)
{
    OrderData = InOrderData;
}