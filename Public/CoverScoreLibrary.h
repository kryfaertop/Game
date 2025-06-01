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
	 * Вычисляет итоговый CoverScore с учётом расстояния до игрока, врага и видимости.
	 * @param DistanceToPlayer - расстояние до игрока
	 * @param DistanceToEnemy - расстояние до врага (AI)
	 * @param VisibilityFactor - 1.0 если видно игрока, 0.0 если нет
	 * @param IdealPlayerDistance - желаемое расстояние до игрока (по умолчанию 800)
	 * @param PlayerSigma - ширина зоны (по умолчанию 300)
	 * @param W1 - вес видимости
	 * @param W2 - вес расстояния до игрока
	 * @param W3 - вес расстояния до врага
	 * @return итоговый CoverScore
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


