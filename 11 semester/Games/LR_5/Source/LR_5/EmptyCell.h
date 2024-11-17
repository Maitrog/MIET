// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "CellState.h"
#include "EmptyCellState.h"

/**
 * 
 */
class LR_5_API EmptyCell : public Cell
{
public:
	EmptyCell();
	~EmptyCell() override;

	virtual CellState* CreateCellState() override;
};
