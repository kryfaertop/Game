// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoverScoreLibrary.generated.h"

UCLASS()
class AIGAME_API UCoverScoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * ��������� �������� CoverScore � ������ ���������� �� ������, ����� � ���������.
	 * @param DistanceToPlayer - ���������� �� ������
	 * @param DistanceToEnemy - ���������� �� ����� (AI)
	 * @param VisibilityFactor - 1.0 ���� ����� ������, 0.0 ���� ���
	 * @param IdealPlayerDistance - �������� ���������� �� ������ (�� ��������� 800)
	 * @param PlayerSigma - ������ ���� (�� ��������� 300)
	 * @param W1 - ��� ���������
	 * @param W2 - ��� ���������� �� ������
	 * @param W3 - ��� ���������� �� �����
	 * @return �������� CoverScore
	 */
	UFUNCTION(BlueprintCallable, Category = "Cover")
	static float CalculateCoverScore(
		float DistanceToPlayer,
		float DistanceToEnemy,
		float VisibilityFactor,
		float IdealPlayerDistance = 800.0f,
		float PlayerSigma = 300.0f,
		float W1 = 10000.0f,
		float W2 = 0.6f,
		float W3 = 0.9f
	);
};


