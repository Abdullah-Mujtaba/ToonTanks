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
        GameOver(false);
        
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) //assigning a variable
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
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
    TargetTowers = GetTowerCount();
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

int32 AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
    //first parameter is the worldcontextobject, an object that should be in the world so we pass this as this game mode exists in our world
    //the next parameters is a UClass, basically telling the function that find actors belonging to this class
    //the last parameter is our array which will contain all the pointers to those class and we call num on it to get the number of towers in our game
    /**
        Unreal makes one info card for every UCLASS when the game starts.
        This card is a UClass object.
        It stores the class name, its variables, functions, default values, etc.

        There is only one card per class for the whole program.
        That’s what people mean by “singleton.”
        (Singleton = one-and-only-instance.)

        StaticClass() simply returns a pointer to that card.
        It does not create anything new; it just says:
        “Here’s the card that represents ATower.”

        Why pass the card around?
        Some engine functions want to know what type to work with, not a specific object.
        Example:

        UGameplayStatics::GetAllActorsOfClass(World, ATower::StaticClass(), Towers);

        The function looks at the card and says,
        “Got it—find every actor in the world whose type is ATower.”
     */
    
    return Towers.Num();
}