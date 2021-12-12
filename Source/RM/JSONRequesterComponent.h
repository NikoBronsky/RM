// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Http.h"
#include "JSONRequesterComponent.generated.h"

// USTRUCT(BlueprintType)
// struct FRMCharInfoStruct
// {
// 	GENERATED_USTRUCT_BODY()
// 		// add stuff you'd like to
// 
// public:
// 	UPROPERTY(EditAnywhere)
// 	int32 CharID = 0;
// 	UPROPERTY(EditAnywhere)
// 	FString Name = "";
// 	UPROPERTY(EditAnywhere)
// 	FString Status = "";
// 	UPROPERTY(EditAnywhere)
// 	FString Species = "";
// 	UPROPERTY(EditAnywhere)
// 	FString Type = "";
// 	UPROPERTY(EditAnywhere)
// 	FString Gender = "";
// 	UPROPERTY(EditAnywhere)
// 	UTexture2D* Image;
// 
// };
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RM_API UJSONRequesterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJSONRequesterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:		

	FHttpModule* Http;

	/* The actual HTTP call */
	UFUNCTION(BlueprintCallable)
	void GetCharacterByID(int32 CharID);

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);



private:

	int32 CharMaximum = 826;
	
	FString DefaultURL = "https://rickandmortyapi.com/api/character/";
};
