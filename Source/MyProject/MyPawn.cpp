// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//player（最小値0番目のプレイヤー）という設定を行う
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//表示するオブジェクトを管理するコンポーネント
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisidleComponent;

	//親子付け可能なダミーのルートコンポーネントを作成
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//カメラオブジェクトを作成
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	//可視オブジェクトを作成（メッシュ）
	OurVisidleComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));


	//RootComponentにカメラを親子付け
	OurCamera->SetupAttachment(RootComponent);

	//（カメラが写す対象の位置に依存するように配置）
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotRotation(FRotator(-45.0f, 0.0f, 0.0f));

	//RootComponentに可視オブジェクト（メッシュ）を親子付け
	OurVisidleComponent->SetupAttachment(RootComponent);

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//移動量があればLocationを更新
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActLoCation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//MoveYの入力値をMove_YAxis関数へバインドする
	InputComponent->BindAxis("MoveY", this,&AMyPawn::Move_YAxis);

	//Growの入力値をバインド
	InputComponent->BindAction("Grow", EInputEvent::IE_Pressed, this, &AMyPawn::StartGrowing);

	InputComponent->BindAction("Grow", EInputEvent::IE_Released, this, &AMyPawn::StopGrowing);
}

