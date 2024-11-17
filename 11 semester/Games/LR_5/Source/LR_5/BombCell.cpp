// Fill out your copyright notice in the Description page of Project Settings.


#include "BombCell.h"

BombCell::BombCell() : Cell()
{
}

BombCell::~BombCell()
{
    delete State;
}

CellState* BombCell::CreateCellState()
{
    return new BombCellState();
}