#pragma once
#include <iostream>
#include <random>

class CMatrix {
private:
	int* m_ptValues;
	int m_totalSize;
	int m_rows;
	int m_columns;
public:
	CMatrix(int rows, int columns); // base ctor.
	CMatrix(const CMatrix& rhs); // copy ctor.
	CMatrix& operator=(const CMatrix& rhs); // assign. ctor.
	~CMatrix(); // dtor.
	int& operator()(int row, int column);
	int& operator()(int row, int column) const;
	CMatrix& operator+=(int scalar);
	CMatrix operator+(int scalar);
	CMatrix& operator-=(int scalar);
	CMatrix operator-(int scalar);
	CMatrix& operator*=(int scalar);
	CMatrix operator*(int scalar);
	CMatrix& operator*=(const CMatrix& rhs);
	CMatrix operator*(const CMatrix& rhs);
	CMatrix& operator+=(const CMatrix& rhs);
	CMatrix operator+(const CMatrix& rhs);
	void reshape(int newRows, int newColumns);
	void show(); //used for dev. only
	void range(int start, int defaultStep = 1);
	void fill(int value);
	void randint(int lowerBound, int upperBound);
};