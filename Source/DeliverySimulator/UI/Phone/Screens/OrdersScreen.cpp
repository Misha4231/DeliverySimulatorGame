// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersScreen.h"

#include "DeliverySimulator/UI/Phone/Components/RestaurantPassObject.h"

void UOrdersScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate)
{
	ScreenChangeDelegate = InScreenChangeDelegate;
}

void UOrdersScreen::NativeConstruct()
{
	Super::NativeConstruct();

	//OrdersList->AddItem()
	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
}

void UOrdersScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!MainGameInstance) MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());

	if (MainGameInstance && MainGameInstance->GetCurrentOrdersLength() != OrdersList->GetNumItems())
	{
		OrdersList->ClearListItems();
		const TArray<FOrder>& CurrentOrders = MainGameInstance->GetCurrentOrders();
		
		for (const FOrder& Order : CurrentOrders)
		{
			URestaurantPassObject* PassObject = NewObject<URestaurantPassObject>(this);
			PassObject->Order = Order;

			OrdersList->AddItem(PassObject); 
		}

	}
}
