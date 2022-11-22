// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalManager.generated.h"

UCLASS()
class PORTALSYSTEM_API APortalManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void AddPortal(class APortal*);

	static inline APortalManager* CurrentPortalManager = nullptr;
	static APortalManager* GetPortalManager();

protected:

	UFUNCTION()
		void OnPortalDestroyed(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable)
		void LinkPortal(APortal* PortalOne, APortal* PortalTwo);
	UFUNCTION(BlueprintCallable)
		void LinkPortalBoth(APortal* PortalOne, APortal* PortalTwo);

private:

	UPROPERTY()
		class APortal* PortalRef;
	UPROPERTY()
		class APortal* PortalRef2;

	UPROPERTY(VisibleAnywhere)
		TArray<class APortal*> Portals;
};
