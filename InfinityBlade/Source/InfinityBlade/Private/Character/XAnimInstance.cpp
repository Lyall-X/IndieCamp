// Fill out your copyright notice in the Description page of Project Settings.


#include "XAnimInstance.h"
#include "Character/XPlayerController.h"
#include "Character/XCharacter.h"
#include "Character/Skill/IceStone.h"
#include "Character/Skill/XBlade.h"


/** 更新人物移动速度 */
void UXAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}

/** 开始播放蒙太奇 */
void UXAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/** 结束播放蒙太奇 */
void UXAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

/** 开始攻击蒙太奇 */
void UXAnimInstance::AnimNotify_AttackStart(UAnimNotify* Notify)
{
	bIsAttacking = true;
}

/** 结束攻击蒙太奇 */
void UXAnimInstance::AnimNotify_AttackEnd(UAnimNotify* Notify)
{
	bIsAttacking = false;
}

/** 重置连击状态 */
void UXAnimInstance::AnimNotify_ResetSerialAttack(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = false;
	bIsEnableThreeAttack = false;
	bIsEnableFourAttack = false;
	bIsEnableFiveAttack = false;
	/** 重置连击伤害 */
	ResetNormalAttack();
}

/** 进入第二次连击 */
void UXAnimInstance::AnimNotify_SecondAttackInput(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = true;
	/** 加成伤害伤害 */
	UpdateSerialAttack();
}

/** 进入第三次连击 */
void UXAnimInstance::AnimNotify_ThreeAttackInput(UAnimNotify* Notify)
{
	bIsEnableThreeAttack = true;
	/** 加成伤害伤害 */
	UpdateSerialAttack();
}

/** 进入第四次连击 */
void UXAnimInstance::AnimNotify_FourAttackInput(UAnimNotify* Notify)
{
	bIsEnableFourAttack = true;
	/** 加成伤害伤害 */
	UpdateSerialAttack();
}

/** 进入第五次连击 */
void UXAnimInstance::AnimNotify_FiveAttackInput(UAnimNotify* Notify)
{
	bIsEnableFiveAttack = true;
	/** 加成伤害伤害 */
	UpdateSerialAttack();
}


/** 初始化玩家状态 */
void UXAnimInstance::InitState()
{
	if (XPlayerState == nullptr)
	{
		/** 获取Controller */
		AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
		/** 获取状态 */
		XPlayerState = XPlayerController->XPlayerState;
		/** 初始化基本攻击 */
		NormalAttack = XPlayerState->GetAttackDamage();
	}
}

/** 重置为普通攻击 */
void UXAnimInstance::ResetNormalAttack()
{
	/** 初始化 */
	InitState();
	/** 重置普攻的伤害 */
	XPlayerState->SetAttackDamage(NormalAttack);
}

/** 连招加成伤害 */
void UXAnimInstance::UpdateSerialAttack()
{
	/** 初始化 */
	InitState();
	/** 加成伤害 */
	XPlayerState->SetAttackDamage(XPlayerState->GetAttackDamage() + 10.f);
}

/** 扣除魔法值 */
void UXAnimInstance::MinusMP(float MP)
{
	/** 初始化 */
	InitState();
	/** 扣除魔法值 */
	XPlayerState->SetCurrentMP(XPlayerState->GetCurrentMP() - MP);
	/** 通知UI */
	UpdateMPUI();
}

/** 更新MP的UI */
void UXAnimInstance::UpdateMPUI()
{
	/** 获取Controller */
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
	/** 获取角色 */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** 设置MP的UI */
	XPlayerController->MainWidget->ProgressBar_MP->SetPercent(1.f - (XPlayerState->GetCurrentMP() / XCharacter->TotalMP));
}

/** 寒冰之石产生通知 */
void UXAnimInstance::AnimNotify_SpawnIceStone(UAnimNotify* Notify)
{
	/** 获取英雄角色 */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** 获取Socket位置 */
	FVector Location = XCharacter->GetMesh()->GetSocketLocation(TEXT("IceStone"));
	/** 获取Socket的旋转 */
	FRotator Rotation = XCharacter->GetMesh()->GetSocketRotation(TEXT("IceStone"));
	/** 产生寒冰之石 */
	AIceStone* IceStone = GetWorld()->SpawnActor<AIceStone>(XCharacter->IceStoneClass, Location, Rotation);
	/** 射出寒冰之石 */
	IceStone->Shoot(Rotation.Vector());
	/** 扣除魔法值 */
	MinusMP(10.f);
}

/** 恢复之术产生通知 */
void UXAnimInstance::AnimNotify_UseCure(UAnimNotify* Notify)
{
	/** 获取英雄角色 */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** 初始化状态 */
	InitState();
	/** 设置当前的HP */
	XPlayerState->SetCurrentHP(XPlayerState->GetCurrentHP() + 30.f);
	/** 判断HP是否溢出 */
	if (XPlayerState->GetCurrentHP() > XCharacter->TotalHP)
	{
		XPlayerState->SetCurrentHP(XCharacter->TotalHP);
	}
	/** 获取Controller */
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
	/** 更新HP的UI */
	XPlayerController->MainWidget->ProgressBar_HP->SetPercent(1.f - (XPlayerState->GetCurrentHP() / XCharacter->TotalHP));
	/** 扣除魔法值 */
	MinusMP(10.f);
}

/** 雷霆之光产生通知 */
void UXAnimInstance::AnimNotify_UseThunder(UAnimNotify* Notify)
{
	/** 初始化状态 */
	InitState();
	/** 扣除魔法值 */
	MinusMP(10.f);
	/** 产生伤害 */
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(TryGetPawnOwner());
	//产生球形伤害
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 50.f, TryGetPawnOwner()->GetActorLocation(), 500.f, nullptr, IgnoreActors, TryGetPawnOwner(), TryGetPawnOwner()->GetController(), true, ECC_Visibility);
}

/** 无尽之刃产生通知 */
void UXAnimInstance::AnimNotify_SpawnXBlade(UAnimNotify* Notify)
{
	/** 获取英雄角色 */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** 产生无尽之刃 */
	AXBlade* XBlade = GetWorld()->SpawnActor<AXBlade>(XCharacter->XBladeClass);
	/** 绑定规则 */
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	/** 绑定无尽之刃 */
	XBlade->AttachToComponent(XCharacter->GetMesh(), AttachmentRules, TEXT("hand_rSocket"));
	/** 扣除魔法值 */
	MinusMP(50.f);
	/** 初始化 */
	InitState();
	/** 加成伤害 */
	XPlayerState->SetAttackDamage(XPlayerState->GetAttackDamage() + 100.f);
	///** 设置为无尽之刃状态 */
	//bIsXBlade = true;
	///** 开启定时器 */
	//XCharacter->GetWorldTimerManager().SetTimer(TimerHandle, this, &UXAnimInstance::TimerCallback, 10.f, false);
}