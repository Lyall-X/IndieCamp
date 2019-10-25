// Fill out your copyright notice in the Description page of Project Settings.

#include "BagItemWidget.h"

/** 控件创建完成后初始化方法 */
bool UBagItemWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** 初始化使用按钮 */
	UseBtn = Cast<UButton>(GetWidgetFromName(TEXT("BtnUse")));
	/** 绑定点击事件 */
	UseBtn->OnClicked.AddDynamic(this, &UBagItemWidget::UseBtnOnClickedEvent);

	return true;
}

/** 按钮点击事件 */
void UBagItemWidget::UseBtnOnClickedEvent()
{
	if (State == nullptr)
	{
		Controller = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		Character = Cast<AXCharacter>(Controller->GetPawn());
		State = Controller->XPlayerState;
	}

	switch (InfoType)
	{
	case EPickupInfoType::HP:
		State->SetCurrentHP(State->GetCurrentHP() + Num);
		Controller->UpdateUI();
		break;
	case EPickupInfoType::MP:
		break;
	default:
		break;
	}

	for (int i = 0; i < Character->PickupArray.Num(); i++)
	{
		FPickupInfo Info = Character->PickupArray[i];
		if (Info.ID == PickupId)
		{
			Character->PickupArray.RemoveAt(i);
		}
	}

	this->RemoveFromParent();
}
