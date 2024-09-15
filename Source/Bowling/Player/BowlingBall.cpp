// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingBall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bowling/UI/PowerBarWidget.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter)

// Sets default values
ABowlingBall::ABowlingBall()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(StaticMeshComponent);
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PowerBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PowerBarComponent"));
	PowerBarWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MaxForce = 10000.f; 
	CurrentForce = 0.f;

	BeginLaunchTime = -1.0f;
	EndLaunchTime = -1.0f;
	TimeToMaxForce = 3.f;
	
}

// Called when the game starts or when spawned
void ABowlingBall::BeginPlay()
{
	Super::BeginPlay();

	if (UPowerBarWidget* PowerBarWidget = Cast<UPowerBarWidget>(PowerBarWidgetComponent->GetUserWidgetObject()))
	{
		PowerBarWidget->SetOwnerBall(this);
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABowlingBall::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector MovementValue = MovementVector.X * FollowCamera->GetForwardVector() + MovementVector.Y * FollowCamera->GetRightVector();

	MovementValue.Z = 0;
	MovementValue.Normalize();

	StaticMeshComponent->AddForce(MovementValue * 100000);
}

void ABowlingBall::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FInputActionValue::Axis2D LookAxisVector = Value.Get<FInputActionValue::Axis2D>();

	CameraBoom->AddLocalRotation(FRotator(LookAxisVector.Y, LookAxisVector.X, 0));
	FRotator SpringArmRotation = CameraBoom->GetRelativeRotation();
	CameraBoom->SetRelativeRotation(FRotator(SpringArmRotation.Pitch, SpringArmRotation.Yaw, 0));
}

void ABowlingBall::StartLaunchBall(const FInputActionValue& Value)
{
	BeginLaunchTime = GetWorld()->GetTimeSeconds();
	GetWorld()->GetTimerManager().SetTimer(
		PowerBarTimerHandle,
		this,
		&ABowlingBall::UpdateCurrentPowerValue,
		0.01f,
		true); //looping
	PowerBarWidgetComponent->SetVisibility(true, true);

}

void ABowlingBall::LaunchBall(const FInputActionValue& Value)
{
	EndLaunchTime = GetWorld()->GetTimeSeconds();
	if (BeginLaunchTime > -1.0f && EndLaunchTime > -1.0f)
	{
		double DeltaLaunchTime = EndLaunchTime - BeginLaunchTime;

		// This means when we hold for short time -> low force; long time (or max time) -> more force
		float ForceMultiplier = DeltaLaunchTime / TimeToMaxForce;
		if (ForceMultiplier > 1.0f)
			ForceMultiplier = 1.0f;

		FVector MovementVector = FollowCamera->GetForwardVector();

		MovementVector.Z = 0;

		StaticMeshComponent->AddForce(MovementVector * MaxForce * ForceMultiplier);

	}
	//ClearTimer 
	GetWorld()->GetTimerManager().ClearTimer(PowerBarTimerHandle);
	PowerBarWidgetComponent->SetVisibility(false, true);

}

void ABowlingBall::UpdateCurrentPowerValue()
{
	double CurrentTime = GetWorld()->GetTimeSeconds();
	double DeltaLaunchTime = CurrentTime - BeginLaunchTime;
	float ForceMultiplier = DeltaLaunchTime / TimeToMaxForce;
	if (ForceMultiplier > 1.0f)
		ForceMultiplier = 1.0f;
	CurrentForce = MaxForce * ForceMultiplier;
}


// Called every frame
void ABowlingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABowlingBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        // Jumping
        EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Started, this, &ABowlingBall::StartLaunchBall);
        EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Completed, this, &ABowlingBall::LaunchBall);

        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABowlingBall::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABowlingBall::Look);
    }
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}