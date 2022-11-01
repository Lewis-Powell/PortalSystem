// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
//#include "../../../../../../../Epic/UE5/UE_5.0/Engine/Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp"

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
	//const FSceneViewport* GameViewport = GEngine->GameViewport->GetGameViewport();
	//FIntPoint ScreenshotSize = GameViewport->GetSizeXY();
	EPixelFormat PixelFormat = PF_A2B10G10R10;
	bool bIsSRGB = false;
	if (!Portal_RT)
	{
		Portal_RT = NewObject<UTextureRenderTarget2D>(this);
	}
	Portal_RT->ClearColor = FLinearColor::Transparent;
	Portal_RT->InitCustomFormat(1920, 1080, PixelFormat, true); //, PixelFormat, !bIsSRGB
	CapturePortal->TextureTarget = Portal_RT;
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

