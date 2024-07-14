// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_OrdersSlot.h"

bool USG_OrdersSlot::AddOrder(TArray<FRestaurant>& AvailableRestaurants, TArray<FProduct>& AvailableProducts, TArray<FDestination>& AvailableDestinations)
{
	if (CurrentOrders.Num() >= 10) return false;

	FOrder NewOrder = FOrder();
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
