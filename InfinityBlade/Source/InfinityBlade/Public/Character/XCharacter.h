// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Character/Skill/IceStone.h"
#include "XCharacter.generated.h"

/**
 * 英雄角色类
 */
UCLASS()
class INFINITYBLADE_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** 摄像机组件 */
	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraComponent;
	/** 武器类 */
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<AWeapon> XWeaponClass;

public:
	/** 总血量 */
	UPROPERTY(EditAnywhere, Category = "PlayerState")
		float TotalHP;
	/** 总魔法量 */
	UPROPERTY(EditAnywhere, Category = "PlayerState")
		float TotalMP;
	/** 普通攻击伤害 */
	UPROPERTY(EditAnywhere, Category = "PlayerState")
		float NoramlAttack;
	/** 连击动画蒙太奇 */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* SerialAttackMontage;

	/** 寒冰之石类型 */
	UPROPERTY(EditAnywhere, Category = "Skill")
		TSubclassOf<AIceStone> IceStoneClass;
	/** 寒冰之石蒙太奇 */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* IceStoneMontage;
	/** 恢复之术蒙太奇 */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* CureMontage;
public:
	/** 构造方法 */
	AXCharacter();

protected:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;

};
