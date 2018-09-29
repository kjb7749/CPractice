#include "CMatrix.h"

CMatrix::CMatrix(int rows, int columns) : m_rows(rows), m_columns(columns) {
	m_totalSize = m_rows * m_columns;
	m_ptValues = new int[m_totalSize]();
}
CMatrix::CMatrix(const CMatrix& rhs) : m_rows(rhs.m_rows), m_columns(rhs.m_columns) {
	m_totalSize = rhs.m_totalSize;
	m_ptValues = new int[rhs.m_totalSize]();
	std::memcpy(m_ptValues, rhs.m_ptValues, rhs.m_totalSize * sizeof(int));
}
CMatrix& CMatrix::operator=(const CMatrix& rhs) {
	if (&rhs == this) {
		return *this;
	}
	if (m_totalSize == rhs.m_totalSize) {
		std::memcpy(m_ptValues, rhs.m_ptValues, rhs.m_totalSize * sizeof(int));
	}
	else {
		delete[] m_ptValues;
		m_ptValues = new int[rhs.m_totalSize]();
		std::memcpy(m_ptValues, rhs.m_ptValues, rhs.m_totalSize * sizeof(int));
	}
	m_rows = rhs.m_rows;
	m_columns = rhs.m_columns;
	m_totalSize = rhs.m_totalSize;

	return *this;
}
CMatrix::~CMatrix() {
	if (m_ptValues) {
		delete[] m_ptValues;
	}
}
int& CMatrix::operator()(int row, int column) {
	if (row >= m_rows || column >= m_columns) {
		throw std::out_of_range("Index out of bounds");
	}
	return m_ptValues[row * m_columns + column];
}
int& CMatrix::operator()(int row, int column) const {
	if (row >= m_rows || column >= m_columns) {
		throw std::out_of_range("Index out of bounds");
	}
	return m_ptValues[row * m_columns + column];
}
CMatrix& CMatrix::operator+=(int scalar) {
	for (auto i = 0; i < m_totalSize; i++) {
		m_ptValues[i] += scalar;
	}
	return *this;
}
CMatrix CMatrix::operator+(int scalar) {
	CMatrix result(m_rows, m_columns);

	for (auto i = 0; i < m_totalSize; i++) {
		result.m_ptValues[i] = m_ptValues[i] + scalar;
	}
	return result;
}
CMatrix& CMatrix::operator-=(int scalar) {
	for (auto i = 0; i < m_totalSize; i++) {
		m_ptValues[i] -= scalar;
	}
	return *this;
}
CMatrix CMatrix::operator-(int scalar) {
	CMatrix result(m_rows, m_columns);

	for (auto i = 0; i < m_totalSize; i++) {
		result.m_ptValues[i] = m_ptValues[i] - scalar;
	}
	return result;
}
CMatrix& CMatrix::operator*=(int scalar) {
	for (auto i = 0; i < m_totalSize; i++) {
		m_ptValues[i] *= scalar;
	}
	return *this;
}
CMatrix CMatrix::operator*(int scalar) {
	CMatrix result(m_rows, m_columns);

	for (auto i = 0; i < m_totalSize; i++) {
		result.m_ptValues[i] = m_ptValues[i] * scalar;
	}
	return result;
}
CMatrix& CMatrix::operator*=(const CMatrix& rhs) {
	CMatrix result = (*this) * rhs;
	(*this) = result;
	return *this;
}
CMatrix CMatrix::operator*(const CMatrix& rhs) {
	if (m_columns != rhs.m_rows) {
		throw std::length_error("Matrices shapes mismatch");
	}
	CMatrix result(m_rows, rhs.m_columns);
	int sum;
	for (auto i = 0; i < m_rows; i++) {
		for (auto j = 0; j < rhs.m_columns; j++) {
			sum = 0;
			for (auto k = 0; k < m_rows; k++) {
				sum += this->operator()(i, k) * rhs(k, j);
			}
			result(i, j) = sum;
		}
	}
	return result;
}
CMatrix& CMatrix::operator+=(const CMatrix& rhs) {
	CMatrix result = (*this) + rhs;
	(*this) = result;
	return *this;
}
CMatrix CMatrix::operator+(const CMatrix& rhs) {
	if (m_rows != rhs.m_rows || m_columns != rhs.m_columns) {
		throw std::length_error("Matrices shapes mismatch");
	}
	CMatrix result(m_rows, m_columns);
	for (auto i = 0; i < m_totalSize; i++) {
		result.m_ptValues[i] = this->m_ptValues[i] + rhs.m_ptValues[i];
	}
	return result;
}
void CMatrix::reshape(int newRows, int newColumns) {
	if (newRows * newColumns > m_totalSize) {
		throw std::invalid_argument("Total size of new matrix must be unchanged");
	}
	m_rows = newRows;
	m_columns = newColumns;
}
//void CMatrix::show() {
//	std::string delimiter = "";
//	for (auto i = 0; i < m_rows; i++) {
//		delimiter = "";
//		for (auto j = 0; j < m_columns; j++) {
//			std::cout << delimiter << m_ptValues[i * m_columns + j];
//			delimiter = ",";
//		}
//		std::cout << std::endl;
//	}
//}
void CMatrix::range(int start, int defaultStep) {
	int counter = start;
	for (auto i = 0; i < m_totalSize; i++) {
		m_ptValues[i] = counter;
		counter += defaultStep;
	}
}
void CMatrix::fill(int value) {
	for (auto i = 0; i < m_totalSize; i++) {
		m_ptValues[i] = value;
	}
}
//void CMatrix::randint(int lowerBound, int upperBound) {
//	std::random_device rd;
//	std::mt19937 mt;
//	std::uniform_int_distribution<int> dist(lowerBound, std::nextafter(upperBound, __DBL_MAX__));
//	for (auto i = 0; i < m_totalSize; i++) {
//		m_ptValues[i] = dist(mt);
//	}
//}