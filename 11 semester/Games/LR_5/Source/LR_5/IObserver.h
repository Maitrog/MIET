// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IObservable.h"

/**
 * 
 */
class LR_5_API IObserver
{
public:
	IObserver();
	virtual ~IObserver();

	virtual void Update(IObservable* subject) = 0;
};
