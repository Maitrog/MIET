// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"

Cell::Cell() {
    State = CreateCellState();
}

bool Cell::IsOpen() const {
    return State->IsOpen;
}

bool Cell::IsBomb() const {
    return dynamic_cast<BombCellState*>(State) != nullptr;
}

void Cell::Attach(IObserver* observer) {
    State->Attach(observer);
}

void Cell::Detach(IObserver* observer) {
    State->Detach(observer);
}

void Cell::Notify() {
    State->Notify();
}

void Cell::Update(IObservable* subject) {
    State->Update(subject);
}

int Cell::Click() {
    return State->Click();
}

bool Cell::RightClick() {
    return State->RightClick();
}

Cell::~Cell() {
    delete State;
}
