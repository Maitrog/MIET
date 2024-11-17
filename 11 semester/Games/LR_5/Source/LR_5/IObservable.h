// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IObserver.h"

/**
 * 
 */
class LR_5_API IObservable
{
public:
	IObservable();
	virtual ~IObservable();

	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};
