// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantPassObject.h"

URestaurantPassObject::URestaurantPassObject()
{
	Restaurant = FRestaurant();
}

URestaurantPassObject::URestaurantPassObject(FRestaurant& InRestaurant)
{
	Restaurant = InRestaurant;
}
