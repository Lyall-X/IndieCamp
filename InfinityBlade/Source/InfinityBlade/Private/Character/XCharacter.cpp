// Fill out your copyright notice in the Description page of Project Settings.


#include "XCharacter.h"

/** 构造方法 */
AXCharacter::AXCharacter()
{
	/** 初始化相机组件 */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CamerComponent");
}

/** 游戏开始调用的方法 */
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


