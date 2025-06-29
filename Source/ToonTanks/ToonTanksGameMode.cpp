// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TankPlayerController.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == tank)
    {
        tank->HandleDestruction();
        if(playerController) //the reason why the rotation was bugged was becuase the pawn class also has a function called
        //GetController which we named our new function to so it was overwriting it
        {
            playerController->SetPlayerEnabledState(false);
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
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0)); //getting the pawn tank
    playerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    StartGame(); 
    //parent = child fine pointer
    //child = parent cast pointer
    //because the function lives there
    if(playerController)
    {   
        playerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(playerController,
            &ATankPlayerController::SetPlayerEnabledState,true);//using ATankPlayerController 
            //third parameter is the input that will be passed to the callback function
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate,StartDelay,false);
        //first we pass the timer handler then we pass the timer delegate because we want to say what should happen when the timer hits
        //last parameter is if we want to loop the condition
    }
}