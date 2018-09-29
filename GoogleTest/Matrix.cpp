#include "Matrix.h"
using namespace dvd;

Matrix::Matrix()
{
	buffer = nullptr;
}
Matrix::~Matrix()
{
	ReleaseBuffer();
}
//행렬의 메모리를 할당하는 생성자입니다
Matrix::Matrix(int row, int col)
{
	buffer = nullptr;
	//매개변수로 주어진 row와 col 만큼의 메모리 공간을 할당합니다
	ReserveBuffer(row, col);
}
//깊은 복사를 진행하는 행렬 복사생성자 입니다
Matrix::Matrix(Matrix& mat)
{
	buffer = nullptr;
	//매개변수로 주어진 row와 col 만큼의 메모리 공간을 할당합니다
	ReserveBuffer(mat.row, mat.col);
	//매개변수 행렬의 각 원소값을 복사합니다
	*this = mat;
}

//행의 개수를 반환하는 함수입니다
int Matrix::getRow()
{
	return row;
}
//열의 개수를 반환하는 함수입니다
int Matrix::getCol()
{
	return col;
}

//할당된 메모리를 초기화 하는 부분입니다
void Matrix::ReleaseBuffer()
{
	//buffer의 값이 nullptr이 아니라면 메모리가 할당되어 있다는 의미이므로
	if (buffer != nullptr)
	{
		//행과 열의 수를 0으로 할당하고 메모리를 해제합니다
		row = col = 0;
		delete[] buffer;
	}
}

//행렬의 공간을 할당하는 함수입니다
void Matrix::ReserveBuffer(int row, int col)
{
	//공간이 이미 할당되어 있을 수도 있으므로 메모리를 먼저 해제합니다
	ReleaseBuffer();
	//새롭게 할당될 행과 열의 수를 저장합니다.
	this->row = row;
	this->col = col;
	//행 * 열 크기의 메모리를 할당합니다
	buffer = new int[row * col];

}

//할당된 행렬의 범위를 넘어가는지 확인하는 함수입니다
bool Matrix::isValidRange(int row, int col)
{
	//매개변수로 받은 row와 col 각각이 0보다 크거나 같고 행렬 최대 row와 col 보다 작으면 true를
	if (row < this->row && col < this->col && row >= 0 && col >= 0)
		return true;
	//그렇지 않다면 false를 반환합니다
	else
		return false;
}

//행렬의 임의의 행과 열의 원소에 값을 설정하는 함수입니다
bool Matrix::SetElement(int row, int col, int value)
{
	//매개변수로 들어온 row와 col이 행렬의 정상적인 범위내 인지 체크하고 그 결과 값을 resultFlag에 저장합니다
	bool resultFlag;
	if (resultFlag = isValidRange(row, col))
	{
		//만약 정상 범위 내라면 매개변수로 받은 value를 해당되는 원소에 할당합니다
		buffer[row*this->col+col] = value;
	}
	return resultFlag;
}

//행렬의 임의의 행과 열의 원소의 값을 받아오는 함수입니다
int Matrix::GetElement(int row, int col)
{
	//매개변수로 들어온 row와 col이 행렬의 정상적인 범위내 인지 체크합니다
	if (isValidRange(row, col))
	{
		//정상이라면 해당되는 행렬의 원소 값을 반환합니다
		return buffer[row*this->col + col];
	}
	else
	{
		//정상이 아니라면 예외를 발생시킵니다
		throw MATRIX_ERROR;
	}
}

//전치 연산이(곱)이 가능한지 확인하는 함수입니다
bool Matrix::isValidTransposeOperation(Matrix& mat)
{
	//자신의 행렬과 매개변수로 주어진 행렬의 행과 열의 값이 각각 같다면 전치 연산이 가능합니다
	if (this->row == mat.col && this->col == mat.row)
		return true;
	else
		return false;
}
//정방 연산(합, 차)이 가능한지 확인하는 함수입니다
bool Matrix::isValidNormalOperation(Matrix& mat)
{
	//자신의 행렬과 매개변수로 주어진 행렬의 행과 행이 열과 열의 값이 같다면 정방 연산이 가능합니다
	if (this->row == mat.row && this->col == mat.col)
		return true;
	else
		return false;
}

Matrix Matrix::Transpose(Matrix& mat)
{
	Matrix a;
	return a;
}

//행렬의 합 연산을 진행하는 연산자 함수입니다
Matrix Matrix::operator +(Matrix& mat)
{
	//정방연산이 가능한지 확인합니다
	if (isValidNormalOperation(mat))
	{
		//가능하다면 새로운 행렬을 생성합니다
		Matrix neo(*this);
		for (int i = 0; i < neo.row; ++i)
		{
			for (int j = 0; j < neo.col; ++j)
			{
				//새롭게 생성된 행렬의 원소에 각 원소값과 매개변수로 주어진 행렬의 각 원소값의 합을 저장합니다.
				neo(i, j, neo.GetElement(i, j) + mat.GetElement(i, j));
			}
		}
		return neo;
	}
	else
		//연산이 불가능 할 경우 예외를 발생시킵니다
		throw MATRIX_ERROR;
}
//행렬의 차 연산을 진행하는 연산자 함수입니다
Matrix Matrix::operator -(Matrix& mat)
{
	//정방연산이 가능한지 확인합니다
	if (isValidNormalOperation(mat))
	{
		//가능하다면 새로운 행렬을 생성합니다
		Matrix neo(*this);
		for (int i = 0; i < neo.row; ++i)
		{
			for (int j = 0; j < neo.col; ++j)
			{
				//새롭게 생성된 행렬의 원소에 각 원소값과 매개변수로 주어진 행렬의 각 원소값의 차를 저장합니다.
				neo(i, j, neo.GetElement(i, j) - mat.GetElement(i, j));
			}
		}
		return neo;
	}
	else
		//연산이 불가능 할 경우 예외를 발생시킵니다
		throw MATRIX_ERROR;
}
//행렬의 곱 연산을 진행하는 연산자 함수입니다
Matrix Matrix::operator *(Matrix& mat)
{
	//전치연산이 가능한지 확인합니다
	if (isValidTransposeOperation(mat))
	{
		//가능하다면 새로운 행렬을 생성합니다
		Matrix neo;
		//전치행렬의 경우 새로운 크기의 배열이 생성되기 때문에 규칙에 맞춰 행렬의 크기를 설정합니다
		neo.ReserveBuffer(row, mat.col);
		for (int i = 0; i < neo.row; ++i)
		{
			for (int j = 0; j < neo.col; ++j)
			{
				int value = 0;
				//각 대응되는 원소의 곱의 합을 축적합니다
				for (int k = 0; k < col; ++k)
				{					
					value += GetElement(i, k) * mat.GetElement(k, j);
				}
				//해당 원소에 두 행렬의 원소곱 합을 할당합니다
				neo(i, j, value);
			}
		}
		return neo;
	}
	else
		//연산이 불가능 할 경우 예외를 발생시킵니다
		throw MATRIX_ERROR;
}
//행렬의 값을 복사하는 함수입니다
Matrix& Matrix::operator =(Matrix& mat)
{
	//정방 연산이 가능한지 확인합니다
	if (isValidNormalOperation(mat))
	{
		for (int i = 0; i < mat.row; ++i)
		{
			for (int j = 0; j < mat.col; ++j)
			{
				//연산이 가능한 경우 각 해당되는 원소의 값을 복사합니다
				SetElement(i, j, mat.GetElement(i, j));
			}
		}
	}
	else
	{
		//정방연산이 불가능한 경우 매개변수로 주어진 행렬의 크기에 맞게 메모리를 다시 할당합니다
		ReserveBuffer(mat.row, mat.col);
		//매개변수로 주어진 행렬의 값을 다시 복사합니다
		*this = mat;
	}
	return *this;
}

bool Matrix::operator ()(int row, int col, int value)
{	
	return SetElement(row, col, value);
}
int Matrix::operator ()(int row, int col)
{
	return GetElement(row, col);
}