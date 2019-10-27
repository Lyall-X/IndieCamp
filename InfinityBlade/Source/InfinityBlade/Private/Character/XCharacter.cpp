// Fill out your copyright notice in the Description page of Project Settings.


#include "XCharacter.h"

/** 构造方法 */
AXCharacter::AXCharacter()
{
	/** 设置角色移动的朝向 */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	/** 设置角色控制器是否控制朝向 */
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	/** 初始化相机组件 */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CamerComponent");
	/** 相机组件绑定父组件 */
	CameraComponent->SetupAttachment(RootComponent);
	/** 相机角色控制器控制朝向 */
	CameraComponent->bUsePawnControlRotation = false;
}

/** 游戏开始调用的方法 */
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


