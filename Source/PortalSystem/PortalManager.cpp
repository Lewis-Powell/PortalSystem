// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalManager.h"
#include "Portal.h"
#include "EngineUtils.h"

// Sets default values
APortalManager::APortalManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortalManager::BeginPlay()
{
	Super::BeginPlay();
	

}

void APortalManager::PopulatePortalsArray()
{
	for (APortal* Portal : TActorRange<APortal>(GetWorld()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ForLoop"));
		if (Portal->Created == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Entered Created"));
			Portals.Add(Portal);
		}
	}
	
}


// Called every frame
void APortalManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Counter == 10)
	{
		UE_LOG(LogTemp, Warning, TEXT("Counter"));
		PopulatePortalsArray();
	}
	Counter++;
	
}

