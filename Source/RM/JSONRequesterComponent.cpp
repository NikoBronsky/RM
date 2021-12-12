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
}


void UJSONRequesterComponent::GetCharacterByID(int32 CharID)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UJSONRequesterComponent::OnResponseReceived);
	//This is the url on which to process the request
	FString URL = DefaultURL + FString::FromInt(CharID);
	Request->SetURL(URL);
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

		//Create a pointer to hold the json serialized data
		TSharedPtr<FJsonObject> JsonObject;

		//Create a reader pointer to read the json data
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		//Deserialize the json data given Reader and the actual object to deserialize
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			//Get the value of the json object by field name
			int32 recievedInt = JsonObject->GetIntegerField("id");
			FString RecievedName = JsonObject->GetStringField("name");

			//Output it to the engine
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green,(RecievedName));

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}



