// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"
#include <Runtime/Engine/Public/EngineUtils.h>
#include <Editor/PListEditor/Private/PListNode.h>
#include <Editor/Blutility/Classes/EditorUtilityTask.h>
#include "PortalWidgetFunctionLib.h"

void UPortalWidgetFunctionLib::GetPortalArray()
{
	Portals.Empty();

	// TODO: Get the editor world
	for (APortal* Portal : TActorRange<APortal>(GEngine->GetWorld()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ForLoop"));
		if (Portal->Created == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Entered Created"));
			Portals.Add(Portal);
		}
	}
}