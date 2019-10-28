// Fill out your copyright notice in the Description page of Project Settings.


#include "XAnimInstance.h"


/** 更新人物移动速度 */
void UXAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}
