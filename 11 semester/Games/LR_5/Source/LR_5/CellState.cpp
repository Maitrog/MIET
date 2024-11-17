// Fill out your copyright notice in the Description page of Project Settings.


#include "CellState.h"

CellState::~CellState()
{
}

CellState::CellState() : IsMark(false), IsOpen(false) {}

void CellState::Detach(IObserver* observer)
{
    Cell* cell = dynamic_cast<Cell*>(observer);
    if (cell) {
        Cells.erase(std::remove(Cells.begin(), Cells.end(), cell), Cells.end());
    }
}

void CellState::Notify()
{
    for (auto cell : Cells) {
        if (GetBombCount() == 0) {
            cell->Update(this);
        }
    }
}

void CellState::Open() {
    if (!IsMark) {
        IsOpen = true;
    }
}

bool CellState::RightClick() {
    if (!IsOpen) {
        IsMark = !IsMark;
    }
    return IsMark;
}

void CellState::Attach(IObserver* observer)
{
    Cell* cell = dynamic_cast<Cell*>(observer);
    if (cell) {
        Cells.push_back(cell);
    }
}
