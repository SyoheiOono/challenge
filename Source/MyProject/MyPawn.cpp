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
	
	//player�i�ŏ��l0�Ԗڂ̃v���C���[�j�Ƃ����ݒ���s��
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//�\������I�u�W�F�N�g���Ǘ�����R���|�[�l���g
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisidleComponent;

	//�e�q�t���\�ȃ_�~�[�̃��[�g�R���|�[�l���g���쐬
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//�J�����I�u�W�F�N�g���쐬
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	//���I�u�W�F�N�g���쐬�i���b�V���j
	OurVisidleComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));


	//RootComponent�ɃJ������e�q�t��
	OurCamera->SetupAttachment(RootComponent);

	//�i�J�������ʂ��Ώۂ̈ʒu�Ɉˑ�����悤�ɔz�u�j
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotRotation(FRotator(-45.0f, 0.0f, 0.0f));

	//RootComponent�ɉ��I�u�W�F�N�g�i���b�V���j��e�q�t��
	OurVisidleComponent->SetupAttachment(RootComponent);

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�ړ��ʂ������Location���X�V
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

	//MoveY�̓��͒l��Move_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MoveY", this,&AMyPawn::Move_YAxis);

	//Grow�̓��͒l���o�C���h
	InputComponent->BindAction("Grow", EInputEvent::IE_Pressed, this, &AMyPawn::StartGrowing);

	InputComponent->BindAction("Grow", EInputEvent::IE_Released, this, &AMyPawn::StopGrowing);
}

