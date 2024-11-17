// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyCellState.h"

EmptyCellState::EmptyCellState() : CellState()
{
}

EmptyCellState::~EmptyCellState()
{
}

int EmptyCellState::Click() {
    if (IsMark) {
        return -2;
    }
    Update(this);
    return GetBombCount();
}

int EmptyCellState::GetBombCount() {
    int count = 0;
    for (auto cell : Cells) {
        if (cell->IsBomb()) {
            count++;
        }
    }
    return count;
}

void EmptyCellState::Update(IObservable* subject) {
    if (!IsOpen) {
        IsMark = false;
        Open();
        if (GetBombCount() == 0) {
            Notify();
        }
    }
}