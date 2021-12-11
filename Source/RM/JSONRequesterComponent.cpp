// Fill out your copyright notice in the Description page of Project Settings.


#include "JSONRequesterComponent.h"
#include "RM.h"

// Sets default values for this component's properties
UJSONRequesterComponent::UJSONRequesterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Http = &FHttpModule::Get();
	// ...
}

// Called when the game starts
void UJSONRequesterComponent::BeginPlay()
{
	Super::BeginPlay();
	MyHttpCall();
	// ...

}


void UJSONRequesterComponent::MyHttpCall()
{

}

void UJSONRequesterComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

}



