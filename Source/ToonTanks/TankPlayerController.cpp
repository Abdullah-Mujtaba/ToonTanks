// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"

 



void ATankPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {
        GetPawn()->EnableInput(this); //accessing the pawn that this controller is attached to 
    }

    else
    {
        GetPawn()->DisableInput(this);  
    }
    bShowMouseCursor = bPlayerEnabled;

}

