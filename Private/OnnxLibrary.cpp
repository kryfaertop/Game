
#include "OnnxLibrary.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include <onnxruntime_cxx_api.h>
#include <mutex>

static Ort::Env* GlobalOrtEnvPtr = nullptr;
static std::once_flag OrtEnvInitFlag;

static void InitOrtEnv()
{
    FString DLLPath = FPaths::ProjectDir() / TEXT("Binaries/Win64/onnxruntime.dll");
    void* Handle = FPlatformProcess::GetDllHandle(*DLLPath);

    if (!Handle)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to manually load onnxruntime.dll!"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("onnxruntime.dll manually loaded."));
    }

    try
    {
        UE_LOG(LogTemp, Warning, TEXT("Attempting to initialize ONNX Runtime..."));

        const OrtApi* api = OrtGetApiBase()->GetApi(ORT_API_VERSION);
        if (api == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("OrtGetApiBase()->GetApi returned nullptr!"));
            GlobalOrtEnvPtr = nullptr;
            return;
        }

        GlobalOrtEnvPtr = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "UE_ONNX");
        UE_LOG(LogTemp, Log, TEXT("ONNX Runtime environment successfully created."));
    }
    catch (const Ort::Exception& e)
    {
        UE_LOG(LogTemp, Error, TEXT("Ort::Env initialization failed: %s"), *FString(e.what()));
        GlobalOrtEnvPtr = nullptr;
    }
}

static void EnsureOrtEnvInitialized()
{
    std::call_once(OrtEnvInitFlag, InitOrtEnv);
}

void UOnnxLibrary::DebugTestOnnxRuntime()
{
    EnsureOrtEnvInitialized();

    if (GlobalOrtEnvPtr == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ONNX Runtime failed to initialize!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("ONNX Runtime is ready to use."));
    }
}

void UOnnxLibrary::RunCoverClassifier(const TArray<float>& InputData, FOnnxResult& OutResult)
{
    OutResult.PredictedClass = -1;
    OutResult.Probabilities.Init(0.0f, 2);

    if (InputData.Num() != 4)
    {
        UE_LOG(LogTemp, Error, TEXT("InputData must contain exactly 4 float values."));
        return;
    }

    EnsureOrtEnvInitialized();
    if (GlobalOrtEnvPtr == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ONNX not initialized"));
        return;
    }

    try
    {
        Ort::SessionOptions SessionOptions;
        SessionOptions.SetIntraOpNumThreads(1);

        FString ModelPath = FPaths::ProjectContentDir() / TEXT("Models/cover_model.onnx");
        std::wstring ModelPathW(*ModelPath);

        Ort::Session Session(*GlobalOrtEnvPtr, ModelPathW.c_str(), SessionOptions);
        Ort::AllocatorWithDefaultOptions Allocator;

        const char* InputName = Session.GetInputNameAllocated(0, Allocator).get();
        std::vector<const char*> OutputNames = {
            Session.GetOutputNameAllocated(0, Allocator).get(),
            Session.GetOutputNameAllocated(1, Allocator).get()
        };

        std::vector<float> InputTensorValues(InputData.GetData(), InputData.GetData() + InputData.Num());
        std::vector<int64_t> InputShape = { 1, 4 };

        Ort::MemoryInfo MemInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        Ort::Value InputTensor = Ort::Value::CreateTensor<float>(
            MemInfo, InputTensorValues.data(), InputTensorValues.size(),
            InputShape.data(), InputShape.size()
        );

        auto OutputTensors = Session.Run(
            Ort::RunOptions{ nullptr },
            &InputName, &InputTensor, 1,
            OutputNames.data(), OutputNames.size()
        );

        int64_t* ClassPtr = OutputTensors[0].GetTensorMutableData<int64_t>();
        OutResult.PredictedClass = static_cast<int32>(*ClassPtr);

        float* Probs = OutputTensors[1].GetTensorMutableData<float>();
        OutResult.Probabilities[0] = Probs[0];
        OutResult.Probabilities[1] = Probs[1];

        UE_LOG(LogTemp, Log, TEXT("ONNX inference completed. Class = %d, Prob0 = %.3f, Prob1 = %.3f"),
            OutResult.PredictedClass, Probs[0], Probs[1]);
    }
    catch (const Ort::Exception& e)
    {
        UE_LOG(LogTemp, Error, TEXT("ONNX inference failed: %s"), *FString(e.what()));
    }
}

















