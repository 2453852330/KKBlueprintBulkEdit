#pragma once

#include "KKBlurprintBulkEditType.generated.h"

USTRUCT(BlueprintType)
struct FKKBPVariableInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName VarType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Category;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString FriendlyName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName VarName;
	FKKBPVariableInfo()=default;
	FKKBPVariableInfo(FName InVarName,FString InFriendlyName,FName InVarType,FText InCategory):
	VarName(InVarName),FriendlyName(InFriendlyName),VarType(InVarType),Category(InCategory){}
};


USTRUCT(BlueprintType)
struct FKKBlueprintWrapper
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBlueprint * BPObj = nullptr;
	FKKBlueprintWrapper()=default;
	FKKBlueprintWrapper(UBlueprint * InObj):BPObj(InObj){}
};

USTRUCT(BlueprintType)
struct FKKFuncEdGraphWrapper
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UEdGraph * Graph = nullptr;
	FKKFuncEdGraphWrapper()=default;
	FKKFuncEdGraphWrapper(UEdGraph * InGraph):Graph(InGraph){}
};

USTRUCT(BlueprintType)
struct FKKGraphInfos
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString Category;
	FKKGraphInfos()=default;
	FKKGraphInfos(FString InName):Name(InName){}
};
