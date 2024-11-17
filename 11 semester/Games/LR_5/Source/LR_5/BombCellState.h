// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellState.h"
#include "IObservable.h"

/**
 * 
 */
class LR_5_API BombCellState : public CellState
{
public:
	BombCellState();
	~BombCellState();

	int Click() override;
	int GetBombCount() override;
	void Update(IObservable* subject) override;
};
