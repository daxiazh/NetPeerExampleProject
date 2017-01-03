// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "NetPeerCallbackProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNetPeerDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNetPeerSuccessedDelegate, int32, Id);

/**
 * 
 */
UCLASS(MinimalAPI)
class UNetPeerCallbackProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
	
		// Called when there is a successful query
		UPROPERTY(BlueprintAssignable)
		FNetPeerDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FNetPeerDelegate OnReconnectFailed;
	// Called when there is an unsuccessful query
	UPROPERTY(BlueprintAssignable)
		FEmptyOnlineDelegate OnFailure;
	
	// Fetches and caches achievement progress from the default online subsystem
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "TestNetPeer")
		static UNetPeerCallbackProxy* ConnectNetPeer(UObject* WorldContextObject, class APlayerController* PlayerController);

	virtual void Activate() override;
	
};
