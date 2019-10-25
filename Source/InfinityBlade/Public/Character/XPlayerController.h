// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/XCharacter.h"
#include "UI/MainUserWidget.h"
#include "Character/XAnimInstance.h"
#include "Character/XPlayerState.h"
#include "UI/CharacterWidget.h"
#include "XPlayerController.generated.h"

/**
 * 主角英雄的控制器
 */
UCLASS()
class INFINITYBLADE_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/** 英雄角色对象 */
	UPROPERTY()
		AXCharacter * XCharacter;
	/** 玩家状态 */
	UPROPERTY()
		AXPlayerState* XPlayerState;
	/** 英雄角色动画实例 */
	UPROPERTY()
		UXAnimInstance* XAnimInstance;
	/** AI数组 */
	UPROPERTY()
		TArray<AActor*> AiArray;
public:
	/** 主界面UI */
	UPROPERTY()
		UMainUserWidget* MainWidget;
	/** 角色用户信息UI */
	UPROPERTY()
		UCharacterWidget* CharacterWidget;
public:
	/** 武器对象 */
	UPROPERTY()
		AWeapon* XWeapon;

public:
	/** 提示信息定时器 */
	FTimerHandle MsgTimer;
	/** 总共冷却时间 */
	float MsgTotalCD;
	/** 当前冷却时间 */
	float MsgCurrentCD;

	/** 寒冰之石定时器 */
	FTimerHandle IceStoneTimer;
	/** 总共冷却时间 */
	float IceStoneTotalCD;
	/** 当前冷却时间 */
	float IceStoneCurrentCD;

public:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
	/** 绑定输入控件 */
	virtual void SetupInputComponent() override;
	/** 重写绑定Character的方法 */
	virtual void Possess(APawn* aPawn) override;

public:
	/** 前后移动 */
	UFUNCTION()
		void MoveForward(float Speed);
	/** 左右移动 */
	UFUNCTION()
		void MoveRight(float Speed);
public:
	/** 初始化玩家状态 */
	void InitState();

	/** 初始化UI */
	void UpdateUI();

	/** 武器伤害方法 */
	UFUNCTION()
		void WeaponOverlapDamage(UPrimitiveComponent* OverlapedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep,const FHitResult& HitResult);
	/** 锁定敌人方法 */
	void LockAI();

	/** 控件按钮事件初始化方法 */
	void InitWidgetEvent();
	/** 攻击按钮点击事件 */
	UFUNCTION()
		void AttackBtnOnClickedEvent();

	/** 寒冰之石技能点击事件 */
	UFUNCTION()
		void IceStoneBtnOnClickedEvent();
	/** 寒冰之石定时器回调方法 */
	void IceStoneCallback();

	/** 恢复之术技能点击事件 */
	UFUNCTION()
		void CureBtnOnClickedEvent();
	/** 雷霆之光技能点击事件 */
	UFUNCTION()
		void ThunderBtnOnClickedEvent();
	/** 无尽之刃技能点击事件 */
	UFUNCTION()
		void XBladeBtnOnClickedEvent();

	/** 消息提示定时器回调方法 */
	void MsgTimerCallback();

	/** 人物角色信息点击事件 */
	UFUNCTION()
		void CharacterBtnOnClickedEvent();
};
