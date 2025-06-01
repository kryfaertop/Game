#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OnnxLibrary.generated.h"

USTRUCT(BlueprintType)
struct FOnnxResult
{
    GENERATED_BODY()

    FOnnxResult()
        : PredictedClass(-1)
    {
        Probabilities.Init(0.0f, 2);
    }

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 PredictedClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<float> Probabilities;
};

UCLASS()
class AIGAME_API UOnnxLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "ONNX")
    static void DebugTestOnnxRuntime();

    UFUNCTION(BlueprintCallable, Category = "ONNX")
    static void RunCoverClassifier(const TArray<float>& InputData, FOnnxResult& OutResult);
};






