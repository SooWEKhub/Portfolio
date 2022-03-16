// Copyright Piotr Sowka, 2022

#include "MineSWRBlockGrid.h"
#include "MineSWR.h"
#include "MineSWRBlock.h"
#include "MineSWRPawn.h"
#include "WebSocketsModule.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AMineSWRBlockGrid::AMineSWRBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	//Set defaults

	BlockSpacing = 300.f;
}

void AMineSWRBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	SizeX = 10;
	SizeY = 10;

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket("wss://hometask.eg1236.com/game1/");

	WebSocket->OnConnected().AddLambda([]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Connected to server");

		});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);

		});

	WebSocket->OnMessage().AddUFunction(this, FName("OnSocketReceiveMessage"));

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Send message "+MessageString);
		});

	WebSocket->Connect();
	WebSocket->Send("new 1");

}

void AMineSWRBlockGrid::OnSocketReceiveMessage(const FString& Message)
{
	if (Message.Mid(0, 3) == "map")
	{
		//GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Yellow, Message);
		MapLevel = Message;
		TArray<AActor*> ActorsToFind;
		if (UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMineSWRBlock::StaticClass(), ActorsToFind);
		}
		for (AActor* FireEffectActor : ActorsToFind)

		{
			//Is this Actor of type FireEffect class?
			AMineSWRBlock* FireEffectCast = Cast<AMineSWRBlock>(FireEffectActor);
			if (FireEffectCast)
			{
				
				int blocknb = FireEffectCast->BlockNb;
				int mapnb = blocknb % SizeX + (blocknb / SizeX) * (SizeX+1)+5;
				FString mapnb_str = *Message.Mid(mapnb, 1);
				int mapnb_int = FCString::Atoi(*mapnb_str);
				if (mapnb_str == "0")
				{
					FireEffectActor->Destroy();
					FVector loc = FireEffectActor->GetActorLocation();
					ATextRenderActor *Text = GetWorld()->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), loc, FRotator(90.f, 180.f, 0.f));
					Text->GetTextRender()->SetText(FText::FromString(TEXT("0")));
					Text->GetTextRender()->SetTextRenderColor(FColor::Red);
					Text->SetActorScale3D(FVector(8.f, 8.f, 8.f));
				}
				if (mapnb_int > 0)
				{
					FireEffectActor->Destroy();
					FVector loc = FireEffectActor->GetActorLocation();
					ATextRenderActor* Text = GetWorld()->SpawnActor<ATextRenderActor>(ATextRenderActor::StaticClass(), loc, FRotator(90.f, 180.f, 0.f));
					Text->GetTextRender()->SetText(FText::FromString(mapnb_str));
					Text->GetTextRender()->SetTextRenderColor(FColor::Red);
					Text->SetActorScale3D(FVector(8.f, 8.f, 8.f));
				}

			}
		}
		
	}
	else if (Message== "open: You lose")
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Red, Message);
	}
	else if (Message == "new: OK")
	{
		TArray<AActor*> ActorsToFind;
		if (UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMineSWRBlock::StaticClass(), ActorsToFind);
		}
		for (AActor* FireEffectActor : ActorsToFind)

		{
			//Is this Actor of type FireEffect class?
			AMineSWRBlock* FireEffectCast = Cast<AMineSWRBlock>(FireEffectActor);
			if (FireEffectCast)
			{
				FireEffectCast->Destroy();
			}
		}
		if (UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATextRenderActor::StaticClass(), ActorsToFind);
		}
		for (AActor* FireEffectActor : ActorsToFind)

		{
			//Is this Actor of type FireEffect class?
			ATextRenderActor* FireEffectCast = Cast<ATextRenderActor>(FireEffectActor);
			if (FireEffectCast)
			{
				if (FireEffectCast->GetName() != "HUD") { FireEffectCast->Destroy(); }
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Yellow, Message);
		for (int32 BlockIndex = 0; BlockIndex < SizeY; BlockIndex++)
		{
			for (int32 BlockIndex1 = 0; BlockIndex1 < SizeX; BlockIndex1++)
			{
				const float YOffset = BlockIndex1 * BlockSpacing;
				const float XOffset = BlockIndex * BlockSpacing;
				const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
				AMineSWRBlock* NewBlock = GetWorld()->SpawnActor<AMineSWRBlock>(BlockLocation, FRotator(0, 0, 0));
				if (NewBlock != nullptr)
				{
					NewBlock->OwningGrid = this;
					NewBlock->BlockNb = BlockIndex * SizeX + BlockIndex1;
				}
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Orange, Message);
	}
}

void AMineSWRBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));

}

#undef LOCTEXT_NAMESPACE
