// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h" //so we can use the 





// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //because we do not need to call tick every single time for tick improves performance as well
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = 1300.f;
	ProjectileMovement->InitialSpeed = 1300.f;
	SmokeTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke trail"));
	SmokeTrail->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit); 
	//we are binding the function to the delegate in beginplay so it happens early on we are not doing this inside the constructor
	//because it can cause issues such that the delegate not being defined
	//the first parameter is the class that we are binding the function for 
	//second parameter is the address of the function that we want to bind
	
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());  //calling it in beginplay because for the projectile
		//begin play happens when it spawns
	}
	

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//the first paraemter is the mesh of our projectile that will cause the hit
//the second parameter is the actor that we hit
//the third parameter is the component of the actor that we hit
//the fourth parameter is the impulse that the physics engine will add when we hit the object the vector will store the direction
//and magnitude of that vector
//the last parameter will hold all the hit information such as locationa and what not
void AProjectile::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner(); //stores the owner
	if(MyOwner == nullptr)
	{
		Destroy(); //destroying the object because if no owner then why exist
		return;
	}
	auto MyOwnerInstigator = MyOwner->GetInstigatorController(); //gets the controller of the actor that shot
	auto DamageTypeClass = UDamageType::StaticClass(); //creating this so we can use the default damagetype and fill the input parameter

	//we do not want to cause damage to ourselves if we are the projectile
	if(OtherActor && OtherActor != this && OtherActor!= MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);
		//when we call this it will generate the damagevent
		//the ontakedamage delegate will then broadcast to its function that are binded
		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
		}
		//the parameters are a worldcontextobject, ar particlesystem, location and rotation where we want to spawn/emit the effect
		//since this is the last location before particle is destroyed it will spawn when it hits the person 
		if(HitSound)
		{	
			UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());//playing before death
		}
	
	}
	// UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation()); this over here works too but there is no check for this
	Destroy(); //so the projectile destroys itself;
	//outside becuase if we hit something no matter what it is destroyed or if it fails to pass all the ifs it still gets destroyed
}
