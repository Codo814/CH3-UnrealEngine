// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
//생성자 - 메모리에 생김, 딱 한번 호출
//PostInitializecomponents() - 컴포넌트가 완성된 직후 호출. 컴포넌트끼리 데이터 주고받기, 상호작용
//BeginPlay() - 배치(Spawn)이후
//Destroyed() - 삭제되기 직전 호출
//EndPlay() - 게임 종료ㅡ 파괴(Desrtoyed()), 레벨 전환
