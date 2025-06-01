// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoverLogLibrary.generated.h"

UCLASS()
class AIGAME_API UCoverLogLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Cover|Log")
    static void SaveLogToFile(const FString& FileName, const TArray<FString>& Lines);
};