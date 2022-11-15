// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include <Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h>
#include "PortalManagerEditorWidget.generated.h"

/**
 * 
 */

UCLASS(meta = (ShowWorldContextPin), config = Editor)
class PORTALSYSTEM_API UPortalManagerEditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintImplementableEvent)
		void LinkButton();

	UFUNCTION(BlueprintCallable)
		void GetPortalArray();

private:

	
	 //APortalManager* PortalManager = APortalManager::GetPortalManager();
	TArray<class APortal*> Portals;
};
