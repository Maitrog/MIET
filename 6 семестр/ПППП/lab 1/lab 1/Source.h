#pragma once

void CreateMatrix(int**& matrix, const int& row, const int& col);

void InitializeMatrix(int** matrix, const int& row, const int& col);

void PrintMatrix(int** matrix, const int& row, const int& col);

void AutoInitializeMatrix(int** matrix, const int& row, const int& col);

void CreateZeroMatrix(int**& matrix, const int& row, const int& col);

void CopyMatrix(int** from, int** to, const int& row, const int& col);

void DeleteMatrix(int** matrix, const int& row);

int GetNormalizedMatrixSize(const int& rowLeftMatrix, const int& rowRightMatrix, const int& colLeftMatrix, const int& colRightMatrix);

void InitializeMatrixSize(int& rowLeftMatrix, int& colLeftMatrix, const char* str);

void ResizeMatrix(int**& matrix, const int& oldRow, const int& oldCol, const int& newRow, const int& newCol);