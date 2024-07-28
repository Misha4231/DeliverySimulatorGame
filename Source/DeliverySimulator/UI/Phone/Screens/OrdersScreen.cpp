// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersScreen.h"
#include "DeliverySimulator/UI/Phone/Components/RestaurantPassObject.h"
#include "OrderDetailsScreen.h"

void UOrdersScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate)
{
	ScreenChangeDelegate = InScreenChangeDelegate;
	ChangeToCreatedScreenDelegate = InChangeToCreatedScreenDelegate;
}

void UOrdersScreen::NativeConstruct()
{
	Super::NativeConstruct();

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
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("Order #") + FString::FormatAsNumber(Order.Id) + FString(" created"));

			URestaurantPassObject* PassObject = NewObject<URestaurantPassObject>(this);
			PassObject->Order = Order;
			PassObject->OrdersScreenObject = this;
			PassObject->OnOrderTaken = &UOrdersScreen::OnOrderTaken;
			PassObject->OnGoToDetails = &UOrdersScreen::OnGoToDetails;

			OrdersList->AddItem(PassObject);
		}

	}
}

void UOrdersScreen::OnOrderTaken(int Id) {
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("Order #") + FString::FormatAsNumber(Id) + FString(" taken"));
}

void UOrdersScreen::OnGoToDetails(URestaurantPassObject* SelectedOrder) {
	if (UOrderDetailsScreen* OrderDetailsScreenWidget = Cast<UOrderDetailsScreen>(CreateWidget<UUserWidget>(this, OrderDetailsScreenClass))) {

		OrderDetailsScreenWidget->SetOrderData(SelectedOrder);

		if (ChangeToCreatedScreenDelegate.IsBound()) {
			ChangeToCreatedScreenDelegate.Execute(OrderDetailsScreenWidget);
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("Go to details of order #") + FString::FormatAsNumber(SelectedOrder->Order.Id));
}