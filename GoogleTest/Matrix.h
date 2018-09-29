#pragma once
#define MATRIX_ERROR -2147483648

namespace dvd
{
	//2차원 연산을 위한 행렬 클래스입니다
	class Matrix
	{
	private:
		//각 원소들을 저장할 메모리 공간입니다
		int* buffer;
		//행의 개수를 저장하는 공간입니다
		int row;
		//열의 개수를 저장하는 공간입니다
		int col;

	private:
		//할당된 메모리를 초기화 하는 부분입니다
		void ReleaseBuffer();
		//할당된 행렬의 범위를 넘어가는지 확인하는 함수입니다
		bool isValidRange(int row, int col);
		//전치 연산이(곱)이 가능한지 확인하는 함수입니다
		bool isValidTransposeOperation(Matrix& mat);
		//정방 연산(합, 차)이 가능한지 확인하는 함수입니다
		bool isValidNormalOperation(Matrix& mat);

	public:
		Matrix();
		//행렬의 메모리를 할당하는 생성자입니다
		Matrix(int row, int col);
		~Matrix();
		//깊은 복사를 진행하는 행렬 복사생성자 입니다
		Matrix(Matrix& mat);

		//행의 개수를 반환하는 함수입니다
		int getRow();
		//열의 개수를 반환하는 함수입니다
		int getCol();

		//행렬의 공간을 할당하는 함수입니다
		void ReserveBuffer(int row, int col);
		//행렬의 임의의 행과 열의 원소에 값을 설정하는 함수입니다
		bool SetElement(int row, int col, int value);
		//행렬의 임의의 행과 열의 원소의 값을 받아오는 함수입니다
		int GetElement(int row, int col);

		//행렬의 전치행렬을 만들어주는 함수입니다
		Matrix Transpose(Matrix& mat);

		//행렬의 합 연산을 진행하는 연산자 함수입니다
		Matrix operator +(Matrix& mat);
		//행렬의 차 연산을 진행하는 연산자 함수입니다
		Matrix operator -(Matrix& mat);
		//행렬의 곱 연산을 진행하는 연산자 함수입니다
		Matrix operator *(Matrix& mat);
		//행렬의 값을 복사하는 함수입니다
		Matrix& operator =(Matrix& mat);

		bool operator ()(int row, int col, int value);
		int operator ()(int row, int col);
	};
}