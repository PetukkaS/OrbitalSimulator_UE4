// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityObject.h"

// Sets default values
AGravityObject::AGravityObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGravityObject::BeginPlay()
{
	Super::BeginPlay();
	
	this->CurrentVelocity = this->InitialVelocity;
}

// Called every frame
void AGravityObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float TimeMultiplier = 1.f;
	float TimeMultiplier = 1000000.f;

	UpdatePosition(DeltaTime*TimeMultiplier);

	//UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);
}

void AGravityObject::UpdatePosition(float DeltaTime)
{
	float AU = 149597870700.f; // m
	//float AU = 1.f; 

	// Take the Unreal Scale into consideration
	FVector CurrentLocation = this->GetActorLocation();
	FVector NewLocation = CurrentLocation + DeltaTime*CurrentVelocity*100.f/AU;
	this->SetActorLocation(NewLocation);

	DrawDebugLine(GetWorld(), CurrentLocation, NewLocation, FColor(RGB.X, RGB.Y, RGB.Z), true);

	UpdateVelocity(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("This name: %s Position: %f %f %f AU"), *this->GetName(), NewLocation.X, NewLocation.Y, NewLocation.Z);

}

void AGravityObject::UpdateVelocity(float DeltaTime)
{
	CurrentVelocity += Acceleration()*DeltaTime;
}

FVector AGravityObject::Acceleration()
{
	float GravConst = 6.67408E-11;

	//float GravConst = 1;

	float AU = 149597870700.f; // m

	//float AU = 1.f;

	// Earth mass
	float MassMultiplier = 5.972E24; // kg

	// float MassMultiplier = 1.f

	FVector TotalAcceleration = FVector(0.f);

	// Get all the gravity objects ingame
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGravityObject::StaticClass(), FoundActors);

	// Loop through the objects and check for not self referencing
	for (AActor* TActor: FoundActors)
	{
    	AGravityObject* GravityObject = Cast<AGravityObject>(TActor);
 
    	if(GravityObject != nullptr)
		{
			if(GravityObject != this)
			{
				// Calcualate force between the bodies

				// Distances in Unreal Scale
				FVector Dir =  GravityObject->GetActorLocation() - this->GetActorLocation();

				float Acceleration = GravConst*GravityObject->GetMass()*MassMultiplier/FMath::Pow((Dir.Size()*AU/100.f),2);

				TotalAcceleration += Acceleration*Dir.GetSafeNormal();
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("This name: %s Acceleration: %f %f %f m/s^2"), *this->GetName(), TotalAcceleration.X/1000.f, TotalAcceleration.Y/1000.f, TotalAcceleration.Z/1000.f);

	return TotalAcceleration;
}

float AGravityObject::GetMass()
{
	return this->Mass;
}

FString AGravityObject::GetName()
{
	return this->Name;
}

