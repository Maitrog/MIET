// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyCell.h"

EmptyCell::EmptyCell() : Cell()
{
}

EmptyCell::~EmptyCell()
{
	delete State;
}

CellState* EmptyCell::CreateCellState()
{
	return new EmptyCellState();
}
