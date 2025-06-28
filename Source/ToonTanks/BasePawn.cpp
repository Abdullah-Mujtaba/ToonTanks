// Fill out your copyright notice in the Description page of Project Settings.



#include "BasePawn.h"
#include "Components/CapsuleComponent.h" //if had not included this file it would have given the error that undefined UCapsuleComponent 
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h" //adding because we are using Aprojectile type in this file

// Sets default values
ABasePawn::ABasePawn() //this is the class constructor
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; //we are basically changing the address of rootcomponent so it points to the capsulecomponent

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp); //attaches this to the capsulecomp
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT ("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(TurretMesh);


}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector targetVector = lookAtTarget - TurretMesh->GetComponentLocation(); //we can use getcomponent location as it provides the location of
	//every component
	FRotator lookAtRotation = FRotator(0.f,targetVector.Rotation().Yaw, 0.f);
	//what this does is only takes out the yaw and makes a FRotator variable and stores nothing fancy just calling a constructor.
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			lookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			15.f)); //FMath::RInterpTo is used here to interpolate the rotaiton so it is smoother
	//it fills in the valeus in between so it is a smoother rotation
	//what setworldrotation does is sets the rotation of the turret mesh to those coordinates
};

void ABasePawn::Fire()
{
	DrawDebugSphere(GetWorld(), ProjectileSpawn->GetComponentLocation(),25.f,12,FColor::Red, false, -3.f);
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawn->GetComponentLocation(),ProjectileSpawn->GetComponentRotation());
	Projectile->SetOwner(this); //doing this so whenever a pawn spawns a projectile it becomes the owner
	//what auto does is lets the compiler figure out the type to assign to the variable
}

// Called when the game starts or when spawned 
// void ABasePawn::BeginPlay()
// {
// 	Super::BeginPlay();
	
// }

// Called every frame
// void ABasePawn::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// 	// FVector DeltaLocation(0.f); //Vector that will tell how much we want to move
// 	// DeltaLocation.X = 2.f;
// 	// AddActorLocalOffset(DeltaLocation);
// }

// Called to bind functionality to input
// void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);

// }

