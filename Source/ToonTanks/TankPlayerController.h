// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetPlayerEnabledState(bool bPlayerEnabled); //setting it to private cuz want to call it from gameMode

};
