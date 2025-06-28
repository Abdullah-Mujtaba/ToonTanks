// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h" //needed for the springArm look at documentation for every header usually
//different components will have different header files also since these were not already inside our base pawn
//class we had to incude them manually
#include "Camera/CameraComponent.h" //needed for the camera
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
ATank::ATank()    
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    springArm->SetupAttachment(RootComponent);
    camera->SetupAttachment(springArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn); //PlayerInputcomponent is how we can map our
    //control bindings to the function/controls
    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire); //IE_Pressed is what tells us that when we press the
    //button linked to this action only then execute the function
    //the reason we were unable to use &ABasePawn::Fire was because the BindAction demands that the pointer should be of the same
    //class where the function is being called so that is why.

}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    controller = Cast<APlayerController>(GetController()); //now what happens is GetController if it returns something of type
    //AplayerController which it does it will store that in our variable otherwise it will be a null ptr
    //GetController returns the type AController so we are not getting the  nullptr
    //DrawDebugSphere(GetWorld(), GetActorLocation()+ FVector(0.f,0.f,200.f),100.f,12,FColor::Red, true, 30.f);
    //GetWorld() returns our world which we need to pass as the first param of drawdebugsphere returns uWorld pointer of our current world
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(controller)
    {
        FHitResult hitResult;
        controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,hitResult);
        //DrawDebugSphere(GetWorld(), hitResult.ImpactPoint,25.f,12,FColor::Red, false, -1.f);
        RotateTurret(hitResult.ImpactPoint);
    }
}

void ATank::Move(float value) //called every second because it is being passed as a parameter in SetupPLayerInputComponent
{
    FVector DeltaLocation(0.f);
    //another way to initialise a function with zero values is 
    //FVector DeltaLocation = FVector::ZeroVector;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X = value*DeltaTime*speed;
    //UE_LOG(LogTemp,Warning,TEXT("Value: %f"), DeltaTime);
    AddActorLocalOffset(DeltaLocation,true); //forgot to add this when testing first and that is why it was not moving
    //UE_LOG(LogTemp,Warning,TEXT("Value: %f"), value);
    //setting the second variable to true so it enables sweep
}

void ATank::Turn(float value)
{
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator DeltaRotation(0.f);
    DeltaRotation.Yaw = value*DeltaTime*rotationSpeed;
    UE_LOG(LogTemp,Warning,TEXT("VALUE: %f"), value);
    AddActorLocalRotation(DeltaRotation);
}

