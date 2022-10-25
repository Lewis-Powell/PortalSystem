// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//m_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_RootComponent"));
	//SetRootComponent(m_RootComponent);
	/*OuterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outer"));
	RootComponent = OuterMesh;*/
	//OuterMesh->SetupAttachment(m_RootComponent);
	//OuterMesh->AttachToComponent(m_RootComponent,);


	OuterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = OuterMesh;
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	CapturePortal = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

