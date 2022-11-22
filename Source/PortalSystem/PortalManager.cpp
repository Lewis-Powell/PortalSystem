// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalManager.h"
#include "Portal.h"
#include "EngineUtils.h"

// Sets default values
APortalManager::APortalManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentPortalManager = this;
}

// Called when the game starts or when spawned
void APortalManager::BeginPlay()
{
	Super::BeginPlay();
}

void APortalManager::OnPortalDestroyed(AActor* DestroyedActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
	Portals.Remove((APortal*)DestroyedActor);
}

void APortalManager::LinkPortalBoth(APortal* PortalOne, APortal* PortalTwo)
{
	check(PortalOne);
	check(PortalTwo);

	PortalOne->LinkedPortal = PortalTwo;
	PortalTwo->LinkedPortal = PortalOne;
}

void APortalManager::LinkPortal(APortal* PortalOne, APortal* PortalTwo)
{
	check(PortalOne);
	check(PortalTwo);

	PortalTwo->LinkedPortal = PortalOne;
}


void APortalManager::AddPortal(APortal* PortalReference)
{
	if (PortalReference != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
		PortalReference->OnDestroyed.AddDynamic(this, &APortalManager::OnPortalDestroyed);
		Portals.Add(PortalReference);
	}
}

APortalManager* APortalManager::GetPortalManager()
{
	return CurrentPortalManager;
}
