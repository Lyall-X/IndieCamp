// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

/** 游戏开始调用的方法 */
void AXPlayerController::BeginPlay()
{

	XCharacter = Cast<AXCharacter>(GetPawn());
	/** 初始化主界面UI */
	MainWidget = CreateWidget<UMainUserWidget>(GetGameInstance(), LoadClass<UMainUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_MainUserWidget.BP_MainUserWidget_C'")));
	/** 添加到视口 */
	MainWidget->AddToViewport();

	/** 判断武器类是否有效 */
	if (XCharacter->XWeaponClass)
	{
		/** 生成一个武器对象 */
		XWeapon = GetWorld()->SpawnActor<AWeapon>(XCharacter->XWeaponClass);
		/** 绑定规则 */
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		/** 绑定武器 */
		XWeapon->AttachToComponent(XCharacter->GetMesh(), AttachmentRules, TEXT("hand_rSocket"));
		/** 绑定武器重叠事件 */
		//pon->CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AXPlayerController::WeaponOverlapDamage);
	}


	/** 初始化按钮点击事件 */
	InitWidgetEvent();
}

/** 绑定输入控件 */
void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/** 绑定输入 */
	InputComponent->BindAxis("MoveForward", this, &AXPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AXPlayerController::MoveRight);
}


/** 前后移动 */
void AXPlayerController::MoveForward(float Speed)
{
	/** 获取控制器的角度 */
	FRotator Rotation = GetControlRotation();
	/** 创建偏航角 */
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/** 获取移动的方向 */
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	/** 在该方向添加位移 */
	XCharacter->AddMovementInput(Direction, Speed);
}

/** 左右移动 */
void AXPlayerController::MoveRight(float Speed)
{
	/** 获取控制器的角度 */
	FRotator Rotation = GetControlRotation();
	/** 创建偏航角 */
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/** 获取移动的方向 */
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	/** 在该方向添加位移 */
	XCharacter->AddMovementInput(Direction, Speed);
}


/** 控件按钮事件初始化方法 */
void AXPlayerController::InitWidgetEvent()
{
	/** 攻击按钮点击事件绑定 */
	if (MainWidget->Button_Attack)
	{
		MainWidget->Button_Attack->OnClicked.AddDynamic(this, &AXPlayerController::AttackBtnOnClickedEvent);
	}
}

/** 攻击按钮点击事件 */
void AXPlayerController::AttackBtnOnClickedEvent()
{
}