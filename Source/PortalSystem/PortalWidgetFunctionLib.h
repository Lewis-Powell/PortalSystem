// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PortalWidgetFunctionLib.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = PortalSystem)
class PORTALSYSTEM_API UPortalWidgetFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable)
		static void GetPortalArray();

private:
	static inline TArray<class APortal*> Portals = TArray<class APortal*>();
};
