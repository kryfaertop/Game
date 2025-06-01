// Fill out your copyright notice in the Description page of Project Settings.

#include "CoverDataSaver.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UCoverDataSaver::SaveStringToFile(const FString& FileName, const FString& SaveText, bool& Success)
{
    FString AbsolutePath = FPaths::ProjectSavedDir() + FileName;
    Success = FFileHelper::SaveStringToFile(SaveText, *AbsolutePath);
}


