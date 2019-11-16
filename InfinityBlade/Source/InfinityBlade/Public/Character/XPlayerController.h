// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/XCharacter.h"
#include "UI/MainUserWidget.h"
#include "Character/XAnimInstance.h"
#include "Character/XPlayerState.h"
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

public:
	/** 主界面UI */
	UPROPERTY()
		UMainUserWidget* MainWidget;
public:
	/** 武器对象 */
	UPROPERTY()
		AWeapon* XWeapon;

public:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
	/** 绑定输入控件 */
	virtual void SetupInputComponent() override;


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
	void UpdateUI();/** 武器伤害方法 */
	UFUNCTION()
		void WeaponOverlapDamage(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult);

	/** 控件按钮事件初始化方法 */
	void InitWidgetEvent();
	/** 攻击按钮点击事件 */
	UFUNCTION()
		void AttackBtnOnClickedEvent();
};
