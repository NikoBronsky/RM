#include "RMAsync.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void URMAsync::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(URL);

	// Setup Async response
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
	{
		FString ResponseString = "";
		if (bSuccess)
		{
			ResponseString = Response->GetContentAsString();
		}

		this->HandleRequestCompleted(ResponseString, bSuccess);
	});

	// Handle actual request
	HttpRequest->ProcessRequest();
}

URMAsync* URMAsync::AsyncRequestHTTP(UObject* WorldContextObject, int32 CharToGet)
{
	FString Result = "https://rickandmortyapi.com/api/character/" + FString::FromInt(CharToGet);
	// Create Action Instance for Blueprint System
	URMAsync* Action = NewObject<URMAsync>();
	Action->URL = Result;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

void URMAsync::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	FRMCharInfoStruct ResultStruct;
	if (bSuccess)
	{
		/* Deserialize object */
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<>::Create(ResponseString);
		FJsonSerializer::Deserialize(JsonReader, JsonObject);


		ResultStruct.CharID = JsonObject->GetIntegerField("id");
		ResultStruct.Name = JsonObject->GetStringField("name");
		ResultStruct.Gender = JsonObject->GetStringField("gender");
		ResultStruct.Species = JsonObject->GetStringField("species");
		ResultStruct.Status = JsonObject->GetStringField("status");
		ResultStruct.Type = JsonObject->GetStringField("type");
		//ResultStruct.Image = JsonObject->GetImage;

		// The simplest example parsing of the plain JSON.
		// Here you can expand to fetch your specific layout of values and objects and return
		// it via a UStruct or separate params in the Completed.Broadcast()
	}


	Completed.Broadcast(ResultStruct, bSuccess);
}