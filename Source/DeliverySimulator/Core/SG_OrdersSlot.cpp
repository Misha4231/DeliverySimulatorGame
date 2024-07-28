// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_OrdersSlot.h"

bool USG_OrdersSlot::AddOrder(TArray<FRestaurant>& AvailableRestaurants, TArray<FProduct>& AvailableProducts, TArray<FDestination>& AvailableDestinations)
{
	if (CurrentOrders.Num() >= 10) return false;

	FOrder NewOrder = FOrder();
	
	if (CurrentOrders.Num() > 0) NewOrder.Id = CurrentOrders.Last().Id + 1;
	else NewOrder.Id = 1;
	
	NewOrder.Restaurant = AvailableRestaurants[FMath::RandRange(0, AvailableRestaurants.Num() - 1)];
	NewOrder.Destination = AvailableDestinations[FMath::RandRange(0, AvailableDestinations.Num() - 1)];
	NewOrder.PercentFee = FMath::RandRange(10, 45);

	int SumQuantity = FMath::RandRange(0, 8);
	
	for (auto Product : AvailableProducts)
	{
		if (SumQuantity <= 0) break;
		
		if (NewOrder.Restaurant.AvailableFoodIds.Contains(Product.Id))
		{
			FOrderProduct NewOrderProduct = FOrderProduct();
			NewOrderProduct.Product = Product;
			NewOrderProduct.Quantity = FMath::RandRange(1, SumQuantity);
			SumQuantity -= NewOrderProduct.Quantity;
			
			NewOrder.ProductList.Add(NewOrderProduct);
		}
	}

	CurrentOrders.Add(NewOrder);
	
	return true;
}

FOrder USG_OrdersSlot::SetCurrentOrderDelivering(int Id) {
	for (auto Order : CurrentOrders) {
		if (Order.Id == Id) {
			CurrentOrderDelivering = Order;
			break;
		}
	}

	return CurrentOrderDelivering;
}

void USG_OrdersSlot::CancelCurrentOrderDelivering() {
	CurrentOrderDelivering = FOrder();
}

float FOrder::CalculateEarnings()
{
    float OrderCost = 0;
	for (const FOrderProduct& Product : this->ProductList)
	{
		OrderCost += Product.Quantity * Product.Product.Price;
    }

	float ClearEarnings = (this->PercentFee * OrderCost) / 100.f;
	float ClearEarningsRounded = FMath::RoundHalfToEven(ClearEarnings * 100.0f) / 100.0f;
	return ClearEarningsRounded;
}
