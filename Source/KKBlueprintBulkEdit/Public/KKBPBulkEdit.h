#pragma once

#include "KKBPBulkEdit.generated.h"

USTRUCT(BlueprintType)
struct FKKBpObjRef
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBlueprint * obj = nullptr;

	FKKBpObjRef():obj(nullptr){}
	FKKBpObjRef(UBlueprint * InObj):obj(InObj){}
};
