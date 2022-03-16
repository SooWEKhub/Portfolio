// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorLabiryntu.h"
#include "Engine/TextRenderActor.h"
#include "Engine/StaticMeshActor.h"
#include "Math/UnrealMathUtility.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AGeneratorLabiryntu::AGeneratorLabiryntu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok1;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok2;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok3;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok4;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok5;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok6;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok7;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok8;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok9;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok10;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok11;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok12;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok13;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok14;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> pok15;

		FConstructorStatics()
			: pok1(TEXT("/Game/Meshes/1.1"))
			, pok2(TEXT("/Game/Meshes/2.2"))
			, pok3(TEXT("/Game/Meshes/3.3"))
			, pok4(TEXT("/Game/Meshes/4.4"))
			, pok5(TEXT("/Game/Meshes/5.5"))
			, pok6(TEXT("/Game/Meshes/6.6"))
			, pok7(TEXT("/Game/Meshes/7.7"))
			, pok8(TEXT("/Game/Meshes/8.8"))
			, pok9(TEXT("/Game/Meshes/9.9"))
			, pok10(TEXT("/Game/Meshes/10.10"))
			, pok11(TEXT("/Game/Meshes/11.11"))
			, pok12(TEXT("/Game/Meshes/12.12"))
			, pok13(TEXT("/Game/Meshes/13.13"))
			, pok14(TEXT("/Game/Meshes/14.14"))
			, pok15(TEXT("/Game/Meshes/15.15"))

		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	pokoj.Add(ConstructorStatics.pok1.Get());
	pokoj.Add(ConstructorStatics.pok2.Get());
	pokoj.Add(ConstructorStatics.pok3.Get());
	pokoj.Add(ConstructorStatics.pok4.Get());
	pokoj.Add(ConstructorStatics.pok5.Get());
	pokoj.Add(ConstructorStatics.pok6.Get());
	pokoj.Add(ConstructorStatics.pok7.Get());
	pokoj.Add(ConstructorStatics.pok8.Get());
	pokoj.Add(ConstructorStatics.pok9.Get());
	pokoj.Add(ConstructorStatics.pok10.Get());
	pokoj.Add(ConstructorStatics.pok11.Get());
	pokoj.Add(ConstructorStatics.pok12.Get());
	pokoj.Add(ConstructorStatics.pok13.Get());
	pokoj.Add(ConstructorStatics.pok14.Get());
	pokoj.Add(ConstructorStatics.pok15.Get());

}

// Called when the game starts or when spawned
void AGeneratorLabiryntu::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Generacja labiryntu rozpoczêta");

	int T[100];
	int KK[99];
	int WK[99];
	int P[3];
	WK[0] = -1;
	KK[0] = 0;
	KK[1] = 1;
	WK[1] = 0;
	KK[2] = 0;
	WK[2] = 1;
	WK[3] = 0;
	KK[3] = -1;
	FVector ofset[14];
	ofset[0] = FVector(0, -30, 0);
	ofset[1] = FVector(30, 0, 0);
	ofset[2] = FVector(40, -40, 0);
	ofset[3] = FVector(0, 30, 0);
	ofset[4] = FVector(0, 0, 0);
	ofset[5] = FVector(40, 40, 0);
	ofset[6] = FVector(70, 0, 0);
	ofset[7] = FVector(-30, 0, 0);
	ofset[8] = FVector(-40, -40, 0);
	ofset[9] = FVector(0, 0, 0);
	ofset[10] = FVector(0, -70, 0);
	ofset[11] = FVector(-40, 40, 0);
	ofset[12] = FVector(-70, 0, 0);
	ofset[13] = FVector(0, 70, 0);
	ofset[14] = FVector(0, 0, 0);

	for (int i = 0; i < 4; i++ )
	{
		P[i] = pow(2, i);
	}
	int DL = 5;
	int SL = 5;
	int liczpom = DL * SL;
	int KOL = SL;
	int L[999];
	DL--;
	SL--;
	int K = FMath::RandRange(0, DL);
	int W = FMath::RandRange(0, SL);
	int LP = 1;
	int Q = 0;
	int R = 0;
	int kierunek = 0;
	int nr = 0;

	for (int32 i = 0; i < (liczpom ); i++)
	{
		L[i] = 0;
	}

	do
	{
		Q = 0;
		if (W > 0) { if (L[K * KOL + W - 1] == 0) { Q++; T[Q] = 0; } }
		if (K < DL) { if (L[(K + 1) * KOL + W] == 0) { Q++; T[Q] = 1; } }
		if (W < SL) { if (L[K * KOL + W + 1] == 0) { Q++; T[Q] = 2; } }
		if (K > 0) { if (L[(K - 1) * KOL + W] == 0) { Q++; T[Q] = 3; } }
		
		if (Q != 0)
		{
			R = FMath::RandRange(1, Q);
			kierunek = T[R];
			L[K * KOL + W] = L[K * KOL + W] + P[kierunek];
			K = K + KK[kierunek];
			W = W + WK[kierunek];
			nr = kierunek - 2;
			if (nr < 0) { nr = nr + 4; }
			L[K * KOL + W] = L[K * KOL + W] + P[nr];
			LP++;
		}
		else
		{
			do
			{
				W++;
				if (W > SL) {
					W = 0; K++; if (K > DL) { K = 0; }
			}
			} while (L[K * KOL + W]==0);
		}

	} while (LP!=liczpom);

	L[0] = L[0] + 1;

	for (int32 i = 0; i < (liczpom); i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::White, FString::FromInt(L[i]));
	}


	for (int32 BlockIndex = 0; BlockIndex < DL+1; BlockIndex++)
	{
		for (int32 BlockIndex1 = 0; BlockIndex1 < SL+1; BlockIndex1++)
		{
			const float YOffset = BlockIndex1 * (-300);
			const float XOffset = BlockIndex * (-300);
			const FVector BlockLocation = FVector(XOffset, YOffset, 170.f) + GetActorLocation()+ofset[L[BlockIndex * KOL + BlockIndex1] - 1];

			AStaticMeshActor* NewBlock = GetWorld()->SpawnActor<AStaticMeshActor>(BlockLocation, FRotator(0, 0, 0));
			if (NewBlock != nullptr)
			{
				NewBlock->GetStaticMeshComponent()->SetStaticMesh(pokoj[L[BlockIndex * KOL + BlockIndex1]-1]);
				NewBlock->SetMobility(EComponentMobility::Movable);
			}
		}
	}

	
}

// Called every frame
void AGeneratorLabiryntu::Tick(float DeltaTime)
{
//	Super::Tick(DeltaTime);
//
//
//	FVector NewLocation = GetActorLocation();
//	FRotator NewRotation = GetActorRotation();
//	float RunningTime = GetGameTimeSinceCreation();
//	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
//	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
//	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
//	NewRotation.Yaw += DeltaRotation;
//	SetActorLocationAndRotation(NewLocation, NewRotation);
//
}

