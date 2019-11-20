// Fill out your copyright notice in the Description page of Project Settings.


#include "XPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Character/Skill/IceStone.h"
#include "AI/AICharacter.h"

/** 游戏开始调用的方法 */
void AXPlayerController::BeginPlay()
{
	/** 设置显示鼠标 */
	bShowMouseCursor = true;

	/** 初始化英雄角色对象*/
	XCharacter = Cast<AXCharacter>(GetPawn());
	/** 初始化英雄角色对象*/
	XAnimInstance = Cast<UXAnimInstance>(XCharacter->GetMesh()->GetAnimInstance());
	/** 初始化玩家状态 */
	XPlayerState = Cast<AXPlayerState>(this->PlayerState);
	/** 初始化玩家状态数值 */
	InitState();

	/** 初始化主界面UI */
	MainWidget = CreateWidget<UMainUserWidget>(GetGameInstance(), LoadClass<UMainUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_MainUserWidget.BP_MainUserWidget_C'")));
	/** 添加到视口 */
	MainWidget->AddToViewport();
	/** 初始化UI */
	UpdateUI();//一定要放在添加视口之后，不然汇报错

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
		XWeapon->CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AXPlayerController::WeaponOverlapDamage);
	}


	/** 初始化按钮点击事件 */
	InitWidgetEvent();

	/** 初始化冷却时间 */
	IceStoneTotalCD = 5.f;
	IceStoneCurrentCD = 0.f;
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
	/** 寒冰之石按钮点击事件绑定 */
	if (MainWidget->Button_IceStone)
	{
		MainWidget->Button_IceStone->OnClicked.AddDynamic(this, &AXPlayerController::IceStoneBtnOnClickedEvent);
	}
	/** 恢复之术按钮点击事件绑定 */
	if (MainWidget->Button_Cure)
	{
		MainWidget->Button_Cure->OnClicked.AddDynamic(this, &AXPlayerController::CureBtnOnClickedEvent);
	}
	/** 雷霆之光按钮点击事件绑定 */
	if (MainWidget->Button_Thunder)
	{
		MainWidget->Button_Thunder->OnClicked.AddDynamic(this, &AXPlayerController::ThunderBtnOnClickedEvent);
	}
	/** 无尽之刃按钮点击事件绑定 */
	if (MainWidget->Button_XBlade)
	{
		MainWidget->Button_XBlade->OnClicked.AddDynamic(this, &AXPlayerController::XBladeBtnOnClickedEvent);
	}
}

/** 攻击按钮点击事件 */
void AXPlayerController::AttackBtnOnClickedEvent()
{
	/** 判断当前蒙太奇是否正在播放,如果正在播放则终止 */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** 获得连击动画蒙太奇 */
	UAnimMontage* SerialAttakMontage = XCharacter->SerialAttackMontage;
	/** 获得当前播放的节 */
	FName CurrentSection = XAnimInstance->Montage_GetCurrentSection(SerialAttakMontage);	
	/** 锁定敌人 */
	LockAI();
	/** 判断 */
	if (CurrentSection.IsNone())
	{
		/** 默认播放第一个节 */
		XAnimInstance->Montage_Play(SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("FirstSection")) && XAnimInstance->bIsEnableSecondAttack)
	{
		/** 播放第二个节 */
		XAnimInstance->Montage_JumpToSection(FName("SecondSection"), SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("SecondSection")) && XAnimInstance->bIsEnableThreeAttack)
	{
		/** 播放第三个节 */
		XAnimInstance->Montage_JumpToSection(FName("ThreeSection"), SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("ThreeSection")) && XAnimInstance->bIsEnableFourAttack)
	{
		/** 播放第四个节 */
		XAnimInstance->Montage_JumpToSection(FName("FourSection"), SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("FourSection")) && XAnimInstance->bIsEnableFiveAttack)
	{
		/** 播放第五个节 */
		XAnimInstance->Montage_JumpToSection(FName("FiveSection"), SerialAttakMontage);
	}
}


/** 初始化玩家状态 */
void AXPlayerController::InitState()
{
	/** 设置一下当前的HP */
	XPlayerState->SetCurrentHP(XCharacter->TotalHP);
	/** 设置一下当前的MP */
	XPlayerState->SetCurrentMP(XCharacter->TotalMP);
	/** 设置一下普攻基本伤害 */
	XPlayerState->SetAttackDamage(XCharacter->NoramlAttack);
}

/** 初始化UI */
void AXPlayerController::UpdateUI()
{
	/** 设置HP */
	if (MainWidget->ProgressBar_HP)
	{
		MainWidget->ProgressBar_HP->SetPercent(1.0 - (XPlayerState->GetCurrentHP() / XCharacter->TotalHP));
	}
	/** 设置MP */
	if (MainWidget->ProgressBar_MP)
	{
		MainWidget->ProgressBar_MP->SetPercent(1.0 - (XPlayerState->GetCurrentMP() / XCharacter->TotalMP));
	}
}

/** 武器伤害方法 */
void AXPlayerController::WeaponOverlapDamage(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	/** 判断武器是否处于攻击状态 */
	if (XAnimInstance->bIsAttacking)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Overlap...");
		UGameplayStatics::ApplyDamage(OtherActor, XPlayerState->GetAttackDamage(), this, XCharacter, nullptr);
	}
}

/** 锁定敌人方法 */
void AXPlayerController::LockAI()
{
	/** 获取自己的位置 */
	FVector Location = XCharacter->GetActorLocation();
	/** 获取所有的敌人列表 */
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), AiArray);
	/** 判断敌人数量 */
	int AiNum = AiArray.Num();
	if (AiNum > 0)
	{
		/** 获取默认最近距离 */
		float MinDistance = FVector::Dist(Location, AiArray[0]->GetActorLocation());
		/** 距离玩家最近的AI */
		AActor* MinActor = AiArray[0];
		/** 遍历所有敌人 */
		for (int i = 0; i < AiNum; i++)
		{
			/** 判断敌人是否已经死亡 */
			if (Cast<AAICharacter>(AiArray[i])->bIsDead)
			{
				continue;
			}
			/** 获取距离 */
			float TmpDistance = FVector::Dist(Location, AiArray[i]->GetActorLocation());
			/** 判断最近距离 */
			if (MinDistance >= TmpDistance)
			{
				MinDistance = TmpDistance;
				MinActor = AiArray[i];
			}
		}
		/** 判断距离是否距离玩家足够的近 */
		if (MinDistance <= 400)
		{
			/** 设置Rotation只左右旋转 */
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Location, MinActor->GetActorLocation());
			/** 修改Rotation */
			Rotation.Pitch = XCharacter->GetCapsuleComponent()->GetComponentRotation().Pitch;
			Rotation.Roll = XCharacter->GetCapsuleComponent()->GetComponentRotation().Roll;
			/** 设置玩家胶囊体朝向 */
			XCharacter->GetCapsuleComponent()->SetRelativeRotation(Rotation);
		}
	}
}

/** 寒冰之石技能点击事件 */
void AXPlayerController::IceStoneBtnOnClickedEvent()
{
	/** 判断寒冰之石蒙太奇是否正在播放 */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** 判断当前魔法值是否足够 */
	if (XPlayerState->GetCurrentMP() >= 10.f)
	{
		LockAI();
		XAnimInstance->Montage_Play(XCharacter->IceStoneMontage, 1.f);
		/** 开始其定时器 */
		XCharacter->GetWorldTimerManager().SetTimer(IceStoneTimer, this, &AXPlayerController::IceStoneCallback, 1.f, true);
		/** 设置当前冷却时间 */
		IceStoneCurrentCD = IceStoneTotalCD;
	}
}

/** 寒冰之石定时器回调方法 */
void AXPlayerController::IceStoneCallback()
{
	if (IceStoneCurrentCD == 0.f)
	{
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Hidden);
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Hidden);
		XCharacter->GetWorldTimerManager().ClearTimer(IceStoneTimer);
	}
	else
	{
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Visible);
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Visible);
		MainWidget->IceStoneCDBar->SetPercent(IceStoneCurrentCD / IceStoneTotalCD);
		MainWidget->IceStoneCDText->SetText(FText::FromString(FString::FromInt(IceStoneCurrentCD) + "s"));
		IceStoneCurrentCD--;
	}
}


/** 恢复之术技能点击事件 */
void AXPlayerController::CureBtnOnClickedEvent()
{
	/** 判断恢复之术蒙太奇是否正在播放 */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** 判断当前魔法值是否足够 */
	if (XPlayerState->GetCurrentMP() >= 10.f)
	{
		if (XPlayerState->GetCurrentHP() < XCharacter->TotalHP)
		{
			XAnimInstance->Montage_Play(XCharacter->CureMontage, 1.f);
		}
		else
		{
			MainWidget->MsgText->SetVisibility(ESlateVisibility::Visible);
			MainWidget->MsgText->SetText(FText::FromString("HP Is MaxValue"));
			MsgCurrentCD = MsgTotalCD;
			XCharacter->GetWorldTimerManager().SetTimer(MsgTimer, this, &AXPlayerController::MsgTimerCallback, 1.f, true);
		}
	}
	else
	{
		MainWidget->MsgText->SetVisibility(ESlateVisibility::Visible);
		MainWidget->MsgText->SetText(FText::FromString("MP Is Not Enough"));
		MsgCurrentCD = MsgTotalCD;
		XCharacter->GetWorldTimerManager().SetTimer(MsgTimer, this, &AXPlayerController::MsgTimerCallback, 1.f, true);
	}
}

/** 雷霆之光技能点击事件 */
void AXPlayerController::ThunderBtnOnClickedEvent()
{
	/** 判断恢复之术蒙太奇是否正在播放 */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** 判断当前魔法值是否足够 */
	if (XPlayerState->GetCurrentMP() >= 30.f)
	{
		XAnimInstance->Montage_Play(XCharacter->ThunderMontage, 1.f);
	}
}


/** 无尽之刃技能点击事件 */
void AXPlayerController::XBladeBtnOnClickedEvent()
{
	/** 判断恢复之术蒙太奇是否正在播放 */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** 判断当前魔法值是否足够 */
	if (XPlayerState->GetCurrentMP() >= 50.f)
	{
		XAnimInstance->Montage_Play(XCharacter->XBladeMontage, 1.f);
	}
}

/** 消息提示定时器回调方法 */
void AXPlayerController::MsgTimerCallback()
{
	if (MsgCurrentCD == 0.f)
	{
		MainWidget->MsgText->SetVisibility(ESlateVisibility::Hidden);
		XCharacter->GetWorldTimerManager().ClearTimer(MsgTimer);
	}
	else
	{
		MainWidget->MsgText->SetVisibility(ESlateVisibility::Visible);
		MsgCurrentCD--;
	}
}