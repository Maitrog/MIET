// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellState.h"
#include "BombCellState.h"

/**
 * 
 */
class LR_5_API EmptyCellState : public CellState
{
public:
	EmptyCellState();
	~EmptyCellState();

	int Click() override;

	int GetBombCount() override;

	void Update(IObservable* subject) override;
};
