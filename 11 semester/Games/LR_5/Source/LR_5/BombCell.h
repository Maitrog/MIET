// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "CellState.h"
#include "BombCellState.h"

/**
 * 
 */
class LR_5_API BombCell : public Cell
{
public:
	BombCell();
	~BombCell();

	virtual CellState* CreateCellState() override;
};
