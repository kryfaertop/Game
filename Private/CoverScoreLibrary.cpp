// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverScoreLibrary.h"
#include "Math/UnrealMathUtility.h"

float UCoverScoreLibrary::CalculateCoverScore(
    float DistanceToPlayer,
    float DistanceToEnemy,
    float VisibilityFactor,
    float IdealPlayerDistance,
    float PlayerSigma,
    float W1,
    float W2,
    float W3)
{
    // ��������� ������ ���������� �� ������ �� ��������� ������
    float Delta = DistanceToPlayer - IdealPlayerDistance;
    float PlayerFactor = FMath::Exp(-(Delta * Delta) / (2 * PlayerSigma * PlayerSigma));

    // ������ ���������� �� ����� (����� � �����)
    float EnemyFactor = 1.0f - FMath::Clamp(DistanceToEnemy / 3000.0f, 0.0f, 1.0f);

    // ����������� CoverScore � ������
    float Score =
        VisibilityFactor * W1 +
        PlayerFactor * W2 +
        EnemyFactor * W3;

    return Score;
}


