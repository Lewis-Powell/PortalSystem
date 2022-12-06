// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Slate/SceneViewport.h"
#include <PortalSystem/PortalManager.h>

#define PORTAL_COOLDOWN 0.01

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
	TeleportPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Teleport Point"));
	TeleportPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	PortalPlane->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapturePortal = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	CapturePortal->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisonBox"));
	m_BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


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

	if (IsValid(LinkedPortal) && IsValid(LinkedPortal->Portal_RT))
	{
		ConstructedRT(LinkedPortal->Portal_RT);
		Created = true;
	}
	//Create interface to run add portal to the portal manager.

	m_BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnCollision);
	AddingPortalToArray();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(LinkedPortal) && !Created)
	{
		ConstructedRT(LinkedPortal->Portal_RT);
		Created = true;
	}
}


void APortal::SetConnectedPortal(APortal* PortalToConnect)
{
	if (PortalToConnect != nullptr)
	{
		PortalConnectedTo = PortalToConnect;
	}
}

void APortal::OnCollision(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (IsValid(LinkedPortal))
	{
		if (LinkedPortal->Cooldown.Contains(OtherActor))
		{
			float time = LinkedPortal->Cooldown[OtherActor];
			UE_LOG(LogTemp, Log, TEXT("1: %f"), time);

			if (time >= GetWorld()->GetTimeSeconds())
			{
				UE_LOG(LogTemp, Log, TEXT("2: failed"));
				return; 
			}

			float portalTime = GetWorld()->GetTimeSeconds() + PORTAL_COOLDOWN;
			LinkedPortal->Cooldown[OtherActor] = portalTime;
			
			if (Cooldown.Contains(OtherActor))
				Cooldown[OtherActor] = portalTime;
			else
				Cooldown.Add(OtherActor, portalTime);

			UE_LOG(LogTemp, Log, TEXT("5: Adding time (%f) %f"), portalTime, GetWorld()->GetTimeSeconds());
		}
		else 
		{
			float portalTime = GetWorld()->GetTimeSeconds() + PORTAL_COOLDOWN;
			LinkedPortal->Cooldown.Add(OtherActor, portalTime);

			if (Cooldown.Contains(OtherActor))
			{
				float time = Cooldown[OtherActor];
				UE_LOG(LogTemp, Log, TEXT("3: %f"), time);

				if (time >= GetWorld()->GetTimeSeconds())
				{
					UE_LOG(LogTemp, Log, TEXT("4: failed"));
					return;
				}

				Cooldown[OtherActor] = portalTime;
			}
			else
				Cooldown.Add(OtherActor, portalTime);

			UE_LOG(LogTemp, Log, TEXT("6: Adding time (%f) %f"), portalTime, GetWorld()->GetTimeSeconds());
		}

		OtherActor->TeleportTo(LinkedPortal->TeleportPoint->GetComponentLocation(), LinkedPortal->TeleportPoint->GetComponentRotation());
	}
}


void APortal::AddingPortalToArray()
{
	APortalManager* PortalManager = APortalManager::GetPortalManager();

	if (PortalManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Portal manager not created before portal init"));
		return;
	}

	PortalManager->AddPortal(this);
}