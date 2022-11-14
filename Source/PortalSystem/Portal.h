// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"


UCLASS()
class PORTALSYSTEM_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		bool Created = false;

	UFUNCTION(BlueprintImplementableEvent)
		void ConstructedRT(UTextureRenderTarget2D* Texture);

	UFUNCTION()
		void SetConnectedPortal(APortal* PortalToConnect);
	
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//	UStaticMeshComponent* OuterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTextureRenderTarget2D* Portal_RT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APortal* PortalOtherFucker;


protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UStaticMeshComponent* PortalPlane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneCaptureComponent2D* CapturePortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* OuterMesh;

private:

	//UProperty Variables

	/*UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OuterMesh;*/
	
	/*UPROPERTY(EditAnywhere)
		class USceneCaptureComponent2D* CapturePortal;*/


	UPROPERTY()
		APortal* PortalConnectedTo;

};
