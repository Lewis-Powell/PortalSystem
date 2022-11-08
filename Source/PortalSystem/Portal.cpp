// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Slate/SceneViewport.h"

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
	PortalPlane->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapturePortal = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	CapturePortal->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//Portal_RT = new UTextureRenderTarget2D();
	//Make resolution of the screen.
	//Portal_RT->SizeX = 1920;
	//Portal_RT->SizeY = 1080;
	

	/*	if (!ScreenshotRT)
		{
			ScreenshotRT = NewObject<UTextureRenderTarget2D>(this);
		}
	ScreenshotRT->ClearColor = FLinearColor::Transparent;
	ScreenshotRT->InitCustomFormat(ScreenshotSize.X, ScreenshotSize.Y, PixelFormat, !bIsSRGB);
}*/

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	if (!Portal_RT)
	{
		Portal_RT = NewObject<UTextureRenderTarget2D>(this);
	}
	Portal_RT->ClearColor = FLinearColor::Red;//Transparent
	Portal_RT->InitAutoFormat(1000, 2000);
	CapturePortal->TextureTarget = Portal_RT;

	if (IsValid(PortalOtherFucker) && IsValid(PortalOtherFucker->Portal_RT))
	{
		ConstructedRT(PortalOtherFucker->Portal_RT);
		Created = true;
	}
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(PortalOtherFucker) && !Created)
	{
		ConstructedRT(PortalOtherFucker->Portal_RT);
		Created = true;
	}
}