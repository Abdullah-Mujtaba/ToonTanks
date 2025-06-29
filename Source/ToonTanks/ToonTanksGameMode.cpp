// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == tank)
    {
        tank->HandleDestruction();
        if(tank->GetTankController()) //the reason why the rotation was bugged was becuase the pawn class also has a function called
        //GetController which we named our new function to so it was overwriting it
        {
            tank->DisableInput(tank->GetTankController());
            tank->GetTankController()->bShowMouseCursor = false;
        }
        
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) //assigning a variable
    {
        DestroyedTower->HandleDestruction();
    } 
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0)); //getting the pawn tank
}
