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
	CallHttp();
	Super::BeginPlay();
}


void UJSONRequesterComponent::CallHttp(FString URL)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UJSONRequesterComponent::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("https://rickandmortyapi.com/api/character?page=2");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UJSONRequesterComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successful"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}



