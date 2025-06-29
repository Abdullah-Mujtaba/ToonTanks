// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h" //to use the type Tank in a cpp file we need to include the header file
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h" //using this because world timer manager returns that type 

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //Find distance to tank
    if(tank)
    {
        float DistanceToTank = FVector::Dist(GetActorLocation(),tank->GetActorLocation());
     
        //see if tank in range
        if(DistanceToTank <= fireRange)
        {
            RotateTurret(tank->GetActorLocation());
        }
        //if in range then rotate toward tank
    
    
    }
    
    
}


void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
};

void ATower::BeginPlay()
{
    Super::BeginPlay();
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));// but because you can’t implicitly convert an APawn* (base) to an 
    //ATank* (derived) without verifying the object’s actual type. 
    //Cast<ATank>() provides that verification, making the line both correct and safe.
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition,FireRate, true); //returns worldtimermanager type 
    //last parameter is for looping that do we want to run this again and again
}

void ATower::CheckFireCondition()
{
    if(tank)
    {
        float DistanceToTank = FVector::Dist(GetActorLocation(),tank->GetActorLocation());
        if(DistanceToTank<fireRange)
        {
            Fire();
        }
    }
}