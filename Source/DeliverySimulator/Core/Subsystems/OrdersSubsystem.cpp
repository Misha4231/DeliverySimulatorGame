// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersSubsystem.h"
#include "Kismet/GameplayStatics.h"


void UOrdersSubsystem::InitializeSubsystem(FString InSaveSlotName, UDataTable *ProductsDataTable, FTimerManager& TimerManger)
{
	InitializeSavingSystem(InSaveSlotName, USG_OrdersSlot::StaticClass());

	if (ProductsDataTable)
	{
		const FString ContextString(TEXT("Product Data Context"));
		TArray<FProduct*> TempArray;
		ProductsDataTable->GetAllRows<FProduct>(ContextString, TempArray);

		for (const FProduct* Product : TempArray)
		{
			Products.Add(*Product);
		}
	}

	OrdersSave = Cast<USG_OrdersSlot>(LoadSlotData());
	TimerManger.SetTimer(OrdersTimerHandle,this, &UOrdersSubsystem::AddOrder, 5.f, true);
}


const TArray<FProduct>& UOrdersSubsystem::GetProducts() const
{
	return Products;
}

TArray<FOrder>& UOrdersSubsystem::GetCurrentOrders()
{
	OrdersSave = Cast<USG_OrdersSlot>(LoadSlotData());
	return OrdersSave->CurrentOrders;
}


FOrder& UOrdersSubsystem::GetCurrentOrder()
{
    OrdersSave = Cast<USG_OrdersSlot>(LoadSlotData());

	return OrdersSave->CurrentOrderDelivering;
}

FOrder UOrdersSubsystem::SetCurrentOrder(int Id)
{
	OrdersSave = Cast<USG_OrdersSlot>(LoadSlotData());

	FOrder Order = OrdersSave->SetCurrentOrderDelivering(Id);
	SaveSlotData(OrdersSave);

	return Order;
}

void UOrdersSubsystem::SetCurrentOrderState(OrderState NewState)
{
	OrdersSave = Cast<USG_OrdersSlot>(LoadSlotData());
	
	if (NewState == OrderState::NotTaken) {
		OrdersSave->RemoveOrder(OrdersSave->CurrentOrderDelivering);
		OrdersSave->CurrentOrderDelivering = FOrder();
		
	} else {
		OrdersSave->CurrentOrderDelivering.State = NewState;
	}

	SaveSlotData(OrdersSave);
}

void UOrdersSubsystem::AddOrder()
{
	FOrder NewOrder = OrdersSave->AddOrder(Restaurants, Products, Destinations);

	if (NewOrder.Id != 0) {
		SaveSlotData(OrdersSave);
		OrdersSave = Cast<USG_OrdersSlot>(LoadSlotData());

		NewOrderDispatcher.Broadcast(NewOrder);
	}
}