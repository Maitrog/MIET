// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellState.h"
#include "IObserver.h"
#include "BombCellState.h"

/**
 * 
 */
class LR_5_API Cell : public IObservable, public IObserver
{
public:
    Cell();
    virtual ~Cell() override;

    CellState* State;

    bool IsOpen() const;

    bool IsBomb() const;

    void Attach(IObserver* observer);

    void Detach(IObserver* observer);

    void Notify();

    void Update(IObservable* subject);

    int Click();

    bool RightClick();

    virtual CellState* CreateCellState() = 0;
};
