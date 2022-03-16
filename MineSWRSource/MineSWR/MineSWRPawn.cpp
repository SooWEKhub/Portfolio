// Copyright Piotr Sowka, 2022

#include "MineSWRPawn.h"
#include "MineSWR.h"
#include "MineSWRBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MineSWRBlockGrid.h"
#include "DrawDebugHelpers.h"
#include "WebSocketsModule.h"
#include "MineSWRBlockGrid.h"

AMineSWRPawn::AMineSWRPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMineSWRPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{			
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			UCameraComponent * OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>();	
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

void AMineSWRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", EInputEvent::IE_Pressed, this, &AMineSWRPawn::OnResetVR);
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AMineSWRPawn::TriggerClick);
	PlayerInputComponent->BindAction("Level1", EInputEvent::IE_Pressed, this, &AMineSWRPawn::level1);
	PlayerInputComponent->BindAction("Level2", EInputEvent::IE_Pressed, this, &AMineSWRPawn::level2);
	PlayerInputComponent->BindAction("Level3", EInputEvent::IE_Pressed, this, &AMineSWRPawn::level3);
	PlayerInputComponent->BindAction("Level4", EInputEvent::IE_Pressed, this, &AMineSWRPawn::level4);
	PlayerInputComponent->BindAction("Up", EInputEvent::IE_Pressed, this, &AMineSWRPawn::Up);
	PlayerInputComponent->BindAction("Down", EInputEvent::IE_Pressed, this, &AMineSWRPawn::Down);
	PlayerInputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &AMineSWRPawn::Left);
	PlayerInputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &AMineSWRPawn::Right);
}

void AMineSWRPawn::Up()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>();
		OurCamera->GetOwner()->SetActorLocation(FVector(OurCamera->GetOwner()->GetActorLocation().X+500, OurCamera->GetOwner()->GetActorLocation().Y, 1500));
	}
}

void AMineSWRPawn::Down()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>();
		OurCamera->GetOwner()->SetActorLocation(FVector(OurCamera->GetOwner()->GetActorLocation().X - 500, OurCamera->GetOwner()->GetActorLocation().Y, 1500));
	}
}

void AMineSWRPawn::Left()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>();
		OurCamera->GetOwner()->SetActorLocation(FVector(OurCamera->GetOwner()->GetActorLocation().X, OurCamera->GetOwner()->GetActorLocation().Y-500, 1500));
	}
}

void AMineSWRPawn::Right()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>();
		OurCamera->GetOwner()->SetActorLocation(FVector(OurCamera->GetOwner()->GetActorLocation().X, OurCamera->GetOwner()->GetActorLocation().Y+500, 1500));
	}
}


void AMineSWRPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void AMineSWRPawn::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMineSWRPawn::TriggerClick()
{
	if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
	}
}
void AMineSWRPawn::level1()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Level 1");
	DiffLevel = 1;
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMineSWRBlock::StaticClass(), ActorsToFind);
	}
	AMineSWRBlock* FireEffectCast = Cast<AMineSWRBlock>(ActorsToFind[0]);
	FireEffectCast->OwningGrid->SizeX = 10;
	FireEffectCast->OwningGrid->SizeY = 10;
	FireEffectCast->OwningGrid->WebSocket->Send("new 1");
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FireEffectCast->OwningGrid->GetName());

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FireEffectCast->OwningGrid->GetName());
}

void AMineSWRPawn::level2()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Level 2");
	DiffLevel = 2;
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMineSWRBlock::StaticClass(), ActorsToFind);
	}
	AMineSWRBlock* FireEffectCast = Cast<AMineSWRBlock>(ActorsToFind[0]);
	FireEffectCast->OwningGrid->SizeX = 40;
	FireEffectCast->OwningGrid->SizeY = 20;
	FireEffectCast->OwningGrid->WebSocket->Send("new 2");
}

void AMineSWRPawn::level3()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Level 3");
	DiffLevel = 3;
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMineSWRBlock::StaticClass(), ActorsToFind);
	}
	AMineSWRBlock* FireEffectCast = Cast<AMineSWRBlock>(ActorsToFind[0]);
	FireEffectCast->OwningGrid->SizeX = 100;
	FireEffectCast->OwningGrid->SizeY = 50;
	FireEffectCast->OwningGrid->WebSocket->Send("new 3");
}

void AMineSWRPawn::level4()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Level 4");
	DiffLevel = 4;
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMineSWRBlock::StaticClass(), ActorsToFind);
	}
	AMineSWRBlock* FireEffectCast = Cast<AMineSWRBlock>(ActorsToFind[0]);
	FireEffectCast->OwningGrid->SizeX = 500;
	FireEffectCast->OwningGrid->SizeY = 50;
	FireEffectCast->OwningGrid->WebSocket->Send("new 4");
}

void AMineSWRPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	//FString BlockName;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		AMineSWRBlock* HitBlock = Cast<AMineSWRBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}