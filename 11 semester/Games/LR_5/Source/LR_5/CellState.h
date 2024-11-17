// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IObservable.h"
#include "IObserver.h"
#include "Cell.h"
#include <vector>

/**
 * 
 */
class LR_5_API CellState : public IObservable, public IObserver
{
public:
    virtual ~CellState() override;

    std::vector<Cell*> Cells;
    bool IsMark;
    bool IsOpen;

    CellState();

    void Open();

    bool RightClick();

    virtual int Click() = 0;
    virtual int GetBombCount() = 0;

    void Attach(IObserver* observer) override;
    void Detach(IObserver* observer) override;
    void Notify() override;

    void Update(IObservable* subject) override = 0;
};
