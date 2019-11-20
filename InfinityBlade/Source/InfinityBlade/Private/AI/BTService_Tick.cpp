// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Tick.h"
#include "AI/MonsterController.h"
#include "AI/AICharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/** 重写心跳节点 */
void UBTService_Tick::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/** 获取Controller */
	AMonsterController* Controller = Cast<AMonsterController>(OwnerComp.GetAIOwner());
	/** 获取黑板控件 */
	UBlackboardComponent* Blackboard = Controller->BlackboardComponent;

	/** 设置SelfLocation */
	Blackboard->SetValueAsVector(TEXT("SelfLocation"), Controller->GetPawn()->GetActorLocation());
	/** 获取AI角色 */
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());
	/** 获取朝向 */
	FRotator Rotation = Monster->GetMesh()->GetComponentRotation();
	/** 设置SelfDirection */
	Blackboard->SetValueAsVector(TEXT("SelfDirection"), Rotation.Vector());

	/** 获取主角位置 */
	FVector TargetLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	/** 设置TargetLocation */
	Blackboard->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
}