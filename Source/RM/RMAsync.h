// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RMAsync.generated.h"

USTRUCT(BlueprintType)
struct FRMCharInfoStruct
{
	GENERATED_USTRUCT_BODY()
		// add stuff you'd like to

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Status = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Species = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Gender = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

};

// Event that will be the 'Completed' exec wire in the blueprint node along with all parameters as output pins.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHttpRequestCompleted, const FRMCharInfoStruct&, CharInfo, bool, bSuccess);
UCLASS() // Change the _API to match your project
class RM_API URMAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:

	void HandleRequestCompleted(FString ResponseString, bool bSuccess);

public:

	/** Execute the actual load */
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "HTTP", WorldContext = "WorldContextObject"))
	static URMAsync* AsyncRequestHTTP(UObject* WorldContextObject, int32 CharToGet);

	UPROPERTY(BlueprintAssignable)
	FOnHttpRequestCompleted Completed;

	/* URL to send GET request to */
	FString URL;

};
