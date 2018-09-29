#pragma once
#define MATRIX_ERROR -2147483648

namespace dvd
{
	//2���� ������ ���� ��� Ŭ�����Դϴ�
	class Matrix
	{
	private:
		//�� ���ҵ��� ������ �޸� �����Դϴ�
		int* buffer;
		//���� ������ �����ϴ� �����Դϴ�
		int row;
		//���� ������ �����ϴ� �����Դϴ�
		int col;

	private:
		//�Ҵ�� �޸𸮸� �ʱ�ȭ �ϴ� �κ��Դϴ�
		void ReleaseBuffer();
		//�Ҵ�� ����� ������ �Ѿ���� Ȯ���ϴ� �Լ��Դϴ�
		bool isValidRange(int row, int col);
		//��ġ ������(��)�� �������� Ȯ���ϴ� �Լ��Դϴ�
		bool isValidTransposeOperation(Matrix& mat);
		//���� ����(��, ��)�� �������� Ȯ���ϴ� �Լ��Դϴ�
		bool isValidNormalOperation(Matrix& mat);

	public:
		Matrix();
		//����� �޸𸮸� �Ҵ��ϴ� �������Դϴ�
		Matrix(int row, int col);
		~Matrix();
		//���� ���縦 �����ϴ� ��� ��������� �Դϴ�
		Matrix(Matrix& mat);

		//���� ������ ��ȯ�ϴ� �Լ��Դϴ�
		int getRow();
		//���� ������ ��ȯ�ϴ� �Լ��Դϴ�
		int getCol();

		//����� ������ �Ҵ��ϴ� �Լ��Դϴ�
		void ReserveBuffer(int row, int col);
		//����� ������ ��� ���� ���ҿ� ���� �����ϴ� �Լ��Դϴ�
		bool SetElement(int row, int col, int value);
		//����� ������ ��� ���� ������ ���� �޾ƿ��� �Լ��Դϴ�
		int GetElement(int row, int col);

		//����� ��ġ����� ������ִ� �Լ��Դϴ�
		Matrix Transpose(Matrix& mat);

		//����� �� ������ �����ϴ� ������ �Լ��Դϴ�
		Matrix operator +(Matrix& mat);
		//����� �� ������ �����ϴ� ������ �Լ��Դϴ�
		Matrix operator -(Matrix& mat);
		//����� �� ������ �����ϴ� ������ �Լ��Դϴ�
		Matrix operator *(Matrix& mat);
		//����� ���� �����ϴ� �Լ��Դϴ�
		Matrix& operator =(Matrix& mat);

		bool operator ()(int row, int col, int value);
		int operator ()(int row, int col);
	};
}