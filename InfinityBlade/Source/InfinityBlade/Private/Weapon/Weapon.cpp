// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

/** 构造方法 */
AWeapon::AWeapon()
{
	/** 初始化武器模型组件 */
	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	/** 设置武器模型的父组件 */
	WeaponComponent->SetupAttachment(RootComponent);
	/** 初始化碰撞体组件 */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	/** 设置碰撞体组件的父组件 */
	CapsuleComponent->SetupAttachment(WeaponComponent);
}