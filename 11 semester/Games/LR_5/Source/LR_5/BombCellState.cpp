// Fill out your copyright notice in the Description page of Project Settings.


#include "BombCellState.h"

BombCellState::BombCellState() : CellState()
{
}

BombCellState::~BombCellState()
{
}

int BombCellState::Click()
{
    if (IsMark)
    {
        return -2;
    }
    return GetBombCount();
}

int BombCellState::GetBombCount()
{
    return -1;
}

void BombCellState::Update(IObservable* subject)
{
}
