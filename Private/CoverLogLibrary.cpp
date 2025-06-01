// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverLogLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

void UCoverLogLibrary::SaveLogToFile(const FString& FileName, const TArray<FString>& Lines)
{
    FString FullPath = FileName;
    FString Output;

    for (FString Line : Lines)
    {
        // Удаляем символы, которые могут испортить CSV
        Line.ReplaceInline(TEXT("\u00A0"), TEXT("")); // неразрывный пробел
        Line.ReplaceInline(TEXT(" "), TEXT(""));
        Line.ReplaceInline(TEXT("\r"), TEXT(""));
        Line.ReplaceInline(TEXT("\n"), TEXT(""));

        Output += Line + TEXT("\n");
    }

    FString FolderPath = FPaths::GetPath(FullPath);
    IFileManager::Get().MakeDirectory(*FolderPath, true);

    // Сохраняем в чистом UTF-8 (без BOM)
    FFileHelper::SaveStringToFile(Output, *FullPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}









