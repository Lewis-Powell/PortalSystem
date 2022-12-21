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

	//Creates the outer mesh for the portal
	OuterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = OuterMesh;
	//Creates the teleport point
	TeleportPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Teleport Point"));
	TeleportPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//The plane which represents the portal itself
	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	PortalPlane->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CapturePortal = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	CapturePortal->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//The collision box for the portal
	m_BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisonBox"));
	m_BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	//If the portal doesn't have a render target it then makes one.
	if (!Portal_RT)
	{
		Portal_RT = NewObject<UTextureRenderTarget2D>(this);
	}
	Portal_RT->ClearColor = FLinearColor::Red;//Transparent
	Portal_RT->InitAutoFormat(1000, 2000);
	CapturePortal->TextureTarget = Portal_RT;

	//If this portal has a valid linked portal and that has a valid render target, construct the render targets in the blueprint function
	if (IsValid(LinkedPortal) && IsValid(LinkedPortal->Portal_RT))
	{
		ConstructedRT(LinkedPortal->Portal_RT);
		Created = true;
	}

	//Adds an event handler for when the box collider begins overlapping
	m_BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnCollision);
	AddingPortalToArray();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Checks if its got a valid linked portal and has not been successfully linked, if this is the case it runs the ConstrucedRT function
	if (IsValid(LinkedPortal) && !Created)
	{
		ConstructedRT(LinkedPortal->Portal_RT);
		Created = true;
	}
}


//Connects this portal to another Portal
void APortal::SetConnectedPortal(APortal* PortalToConnect)
{
	if (PortalToConnect != nullptr)
	{
		PortalConnectedTo = PortalToConnect;
	}
}

//The function is called when a collision occurs and teleports the object if the correct conditions are met
void APortal::OnCollision(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//Does it have a linked portal
	if (IsValid(LinkedPortal))
	{
		//Checks if the cooldown map contains the colliding actor
		if (LinkedPortal->Cooldown.Contains(OtherActor))
		{
			//Gets the time that the actor last passed through the linked portal
			float time = LinkedPortal->Cooldown[OtherActor];
			//UE_LOG(LogTemp, Log, TEXT("1: %f"), time);

			//if the actor hasn't waited long enough to go back through the portal
			if (time >= GetWorld()->GetTimeSeconds())
			{
				//UE_LOG(LogTemp, Log, TEXT("2: failed"));
				return; 
			}
			// Calculates the new time that the actor has to wait before going through another portal.
			float portalTime = GetWorld()->GetTimeSeconds() + PORTAL_COOLDOWN;
			LinkedPortal->Cooldown[OtherActor] = portalTime;
			
			//If it contains the actor updates the time, if it doesn't it adds it to the map
			if (Cooldown.Contains(OtherActor))
				Cooldown[OtherActor] = portalTime;
			else
				Cooldown.Add(OtherActor, portalTime);

			//UE_LOG(LogTemp, Log, TEXT("5: Adding time (%f) %f"), portalTime, GetWorld()->GetTimeSeconds());
		}
		else 
		{
			//Calculates the new time the actor has to wait before going through another cooldown and adds it to the cooldown maps of both portals
			float portalTime = GetWorld()->GetTimeSeconds() + PORTAL_COOLDOWN;
			LinkedPortal->Cooldown.Add(OtherActor, portalTime);
			
			if (Cooldown.Contains(OtherActor))
			{
				
				float time = Cooldown[OtherActor];
				//UE_LOG(LogTemp, Log, TEXT("3: %f"), time);

				//If the time is greater than or equal to the current time in the world it returns from the function
				if (time >= GetWorld()->GetTimeSeconds())
				{
					//UE_LOG(LogTemp, Log, TEXT("4: failed"));
					return;
				}
				//Update this portal's cooldown map with the new time.
				Cooldown[OtherActor] = portalTime;
			}
			//Otherwise, add the new time to this portal's cooldown map for the actor.
			else
				Cooldown.Add(OtherActor, portalTime);

			//UE_LOG(LogTemp, Log, TEXT("6: Adding time (%f) %f"), portalTime, GetWorld()->GetTimeSeconds());
		}

		//Teleport the actor that collided with this portal to the linked portal's teleport point.
		OtherActor->TeleportTo(LinkedPortal->TeleportPoint->GetComponentLocation(), LinkedPortal->TeleportPoint->GetComponentRotation());
	}
}


//Adds a portal to the portal manager array if one exists in the scene
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