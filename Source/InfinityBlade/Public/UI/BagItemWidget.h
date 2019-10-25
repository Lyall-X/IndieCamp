// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/XPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Character/XPlayerController.h"
#include "Character/XCharacter.h"
#include "Pickup/ItemInfo.h"
#include "BagItemWidget.generated.h"

/**
 * 基本Item的UI
 */
UCLASS()
class INFINITYBLADE_API UBagItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		AXCharacter * Character;
	UPROPERTY()
		AXPlayerController * Controller;
	UPROPERTY()
		AXPlayerState* State;
	uint8 PickupId;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock * Name;
	EPickupInfoType InfoType;
	float Num;
	UPROPERTY(Meta = (BindWidget))
		UImage* Pic;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Desc;
	UPROPERTY()
		UButton* UseBtn;

public:
	/** 控件创建完成后初始化方法 */
		virtual bool Initialize() override;
	/** 按钮点击事件 */
	UFUNCTION()
		void UseBtnOnClickedEvent();

	
};
