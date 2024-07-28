// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UMainGameInstance::Init()
{
	Super::Init();

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
	
	LoadOrdersSlotData();
	GetTimerManager().SetTimer(OrdersTimerHandle,this, &UMainGameInstance::AddOrder, 5.f, true);
}

const TArray<FProduct>& UMainGameInstance::GetProducts() const
{
	return Products;
}

const TArray<FOrder>& UMainGameInstance::GetCurrentOrders() const
{
	return Orders;
}

const int UMainGameInstance::GetCurrentOrdersLength() const
{
	return Orders.Num();
}

void UMainGameInstance::CurrentOrderDone()
{
	LoadOrdersSlotData();
	OrdersSave->CancelCurrentOrderDelivering();

	// Give Money on balance
}

void UMainGameInstance::CancelCurrentOrder()
{
	LoadOrdersSlotData();
	OrdersSave->CancelCurrentOrderDelivering();
}

FOrder& UMainGameInstance::GetCurrentOrder()
{
    LoadOrdersSlotData();

	return OrdersSave->CurrentOrderDelivering;
}

FOrder UMainGameInstance::SetCurrentOrder(int Id)
{
	LoadOrdersSlotData();

	FOrder Order = OrdersSave->SetCurrentOrderDelivering(Id);
	SaveOrdersSlotData();

	return Order;
}

void UMainGameInstance::LoadOrdersSlotData()
{
	if(UGameplayStatics::DoesSaveGameExist(OrdersSaveSlotName, 0))
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::LoadGameFromSlot(OrdersSaveSlotName, 0));
		if (OrdersSave)
		{
			Orders = OrdersSave->CurrentOrders;
		}
	} else
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::CreateSaveGameObject(USG_OrdersSlot::StaticClass()));
		UGameplayStatics::SaveGameToSlot(OrdersSave, OrdersSaveSlotName, 0);
	}
}

void UMainGameInstance::SaveOrdersSlotData()
{
	if(UGameplayStatics::DoesSaveGameExist(OrdersSaveSlotName, 0))
	{
		UGameplayStatics::SaveGameToSlot(OrdersSave, OrdersSaveSlotName, 0);
	} else
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::CreateSaveGameObject(USG_OrdersSlot::StaticClass()));
		UGameplayStatics::SaveGameToSlot(OrdersSave, OrdersSaveSlotName, 0);
	}
}

void UMainGameInstance::AddOrder()
{
	OrdersSave->AddOrder(Restaurants, Products, Destinations);
	SaveOrdersSlotData();
	LoadOrdersSlotData();
}
