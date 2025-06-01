// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoverDataSaver.generated.h"

UCLASS()
class AIGAME_API UCoverDataSaver : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Cover Export")
    static void SaveStringToFile(const FString& FileName, const FString& SaveText, bool& Success);
};

