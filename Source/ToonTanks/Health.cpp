// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	//Owner = GetOwner(); //we want to get the owner of this component so we can bind it to its delegate
	//Owner->OnTakeAnyDamage.AddDynamic(this,&UHealth::DamageTaken); //so we binded it to the owners damage delegate
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealth::DamageTaken);
	//in AddDynamic the first parameter is the class which has the callback function
	//only the pawns have the OnTakeAnyDamage delegate
	// ...
	//the error we were getting was due to the wrong name of the delegate
	//what I have done I am commenting out becasue it will use more space 
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage<= 0.f)
	{
		return;
	}

	Health-=Damage;
	UE_LOG(LogTemp,Warning,TEXT("Damage done to the object max health is %f"),Health);


};


