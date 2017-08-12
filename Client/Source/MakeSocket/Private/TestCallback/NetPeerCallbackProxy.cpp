// Fill out your copyright notice in the Description page of Project Settings.
#include "NetPeerCallbackProxy.h"


UNetPeerCallbackProxy* UNetPeerCallbackProxy::ConnectNetPeer(UObject* WorldContextObject, class APlayerController* PlayerController)
{
	UNetPeerCallbackProxy* Proxy = NewObject<UNetPeerCallbackProxy>();	
	// Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}


void UNetPeerCallbackProxy::Activate()
{
}
