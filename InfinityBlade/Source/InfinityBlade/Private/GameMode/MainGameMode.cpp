// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Character/XPlayerController.h"
#include "Character/XPlayerState.h"

/** 构造方法 */
AMainGameMode::AMainGameMode()
{
	/** 找到资源里的Character蓝图类 */
	ConstructorHelpers::FClassFinder<ACharacter> CharacterFinder(TEXT("/Game/Character/Blueprint/BP_XCharacter"));
	DefaultPawnClass = CharacterFinder.Class;
	/** 设置PlayerController */
	PlayerControllerClass = AXPlayerController::StaticClass();
	/** 设置PlayerState */
	PlayerStateClass = AXPlayerState::StaticClass();
};
