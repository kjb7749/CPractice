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
//����� �޸𸮸� �Ҵ��ϴ� �������Դϴ�
Matrix::Matrix(int row, int col)
{
	buffer = nullptr;
	//�Ű������� �־��� row�� col ��ŭ�� �޸� ������ �Ҵ��մϴ�
	ReserveBuffer(row, col);
}
//���� ���縦 �����ϴ� ��� ��������� �Դϴ�
Matrix::Matrix(Matrix& mat)
{
	buffer = nullptr;
	//�Ű������� �־��� row�� col ��ŭ�� �޸� ������ �Ҵ��մϴ�
	ReserveBuffer(mat.row, mat.col);
	//�Ű����� ����� �� ���Ұ��� �����մϴ�
	*this = mat;
}

//���� ������ ��ȯ�ϴ� �Լ��Դϴ�
int Matrix::getRow()
{
	return row;
}
//���� ������ ��ȯ�ϴ� �Լ��Դϴ�
int Matrix::getCol()
{
	return col;
}

//�Ҵ�� �޸𸮸� �ʱ�ȭ �ϴ� �κ��Դϴ�
void Matrix::ReleaseBuffer()
{
	//buffer�� ���� nullptr�� �ƴ϶�� �޸𸮰� �Ҵ�Ǿ� �ִٴ� �ǹ��̹Ƿ�
	if (buffer != nullptr)
	{
		//��� ���� ���� 0���� �Ҵ��ϰ� �޸𸮸� �����մϴ�
		row = col = 0;
		delete[] buffer;
	}
}

//����� ������ �Ҵ��ϴ� �Լ��Դϴ�
void Matrix::ReserveBuffer(int row, int col)
{
	//������ �̹� �Ҵ�Ǿ� ���� ���� �����Ƿ� �޸𸮸� ���� �����մϴ�
	ReleaseBuffer();
	//���Ӱ� �Ҵ�� ��� ���� ���� �����մϴ�.
	this->row = row;
	this->col = col;
	//�� * �� ũ���� �޸𸮸� �Ҵ��մϴ�
	buffer = new int[row * col];

}

//�Ҵ�� ����� ������ �Ѿ���� Ȯ���ϴ� �Լ��Դϴ�
bool Matrix::isValidRange(int row, int col)
{
	//�Ű������� ���� row�� col ������ 0���� ũ�ų� ���� ��� �ִ� row�� col ���� ������ true��
	if (row < this->row && col < this->col && row >= 0 && col >= 0)
		return true;
	//�׷��� �ʴٸ� false�� ��ȯ�մϴ�
	else
		return false;
}

//����� ������ ��� ���� ���ҿ� ���� �����ϴ� �Լ��Դϴ�
bool Matrix::SetElement(int row, int col, int value)
{
	//�Ű������� ���� row�� col�� ����� �������� ������ ���� üũ�ϰ� �� ��� ���� resultFlag�� �����մϴ�
	bool resultFlag;
	if (resultFlag = isValidRange(row, col))
	{
		//���� ���� ���� ����� �Ű������� ���� value�� �ش�Ǵ� ���ҿ� �Ҵ��մϴ�
		buffer[row*this->col+col] = value;
	}
	return resultFlag;
}

//����� ������ ��� ���� ������ ���� �޾ƿ��� �Լ��Դϴ�
int Matrix::GetElement(int row, int col)
{
	//�Ű������� ���� row�� col�� ����� �������� ������ ���� üũ�մϴ�
	if (isValidRange(row, col))
	{
		//�����̶�� �ش�Ǵ� ����� ���� ���� ��ȯ�մϴ�
		return buffer[row*this->col + col];
	}
	else
	{
		//������ �ƴ϶�� ���ܸ� �߻���ŵ�ϴ�
		throw MATRIX_ERROR;
	}
}

//��ġ ������(��)�� �������� Ȯ���ϴ� �Լ��Դϴ�
bool Matrix::isValidTransposeOperation(Matrix& mat)
{
	//�ڽ��� ��İ� �Ű������� �־��� ����� ��� ���� ���� ���� ���ٸ� ��ġ ������ �����մϴ�
	if (this->row == mat.col && this->col == mat.row)
		return true;
	else
		return false;
}
//���� ����(��, ��)�� �������� Ȯ���ϴ� �Լ��Դϴ�
bool Matrix::isValidNormalOperation(Matrix& mat)
{
	//�ڽ��� ��İ� �Ű������� �־��� ����� ��� ���� ���� ���� ���� ���ٸ� ���� ������ �����մϴ�
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

//����� �� ������ �����ϴ� ������ �Լ��Դϴ�
Matrix Matrix::operator +(Matrix& mat)
{
	//���濬���� �������� Ȯ���մϴ�
	if (isValidNormalOperation(mat))
	{
		//�����ϴٸ� ���ο� ����� �����մϴ�
		Matrix neo(*this);
		for (int i = 0; i < neo.row; ++i)
		{
			for (int j = 0; j < neo.col; ++j)
			{
				//���Ӱ� ������ ����� ���ҿ� �� ���Ұ��� �Ű������� �־��� ����� �� ���Ұ��� ���� �����մϴ�.
				neo(i, j, neo.GetElement(i, j) + mat.GetElement(i, j));
			}
		}
		return neo;
	}
	else
		//������ �Ұ��� �� ��� ���ܸ� �߻���ŵ�ϴ�
		throw MATRIX_ERROR;
}
//����� �� ������ �����ϴ� ������ �Լ��Դϴ�
Matrix Matrix::operator -(Matrix& mat)
{
	//���濬���� �������� Ȯ���մϴ�
	if (isValidNormalOperation(mat))
	{
		//�����ϴٸ� ���ο� ����� �����մϴ�
		Matrix neo(*this);
		for (int i = 0; i < neo.row; ++i)
		{
			for (int j = 0; j < neo.col; ++j)
			{
				//���Ӱ� ������ ����� ���ҿ� �� ���Ұ��� �Ű������� �־��� ����� �� ���Ұ��� ���� �����մϴ�.
				neo(i, j, neo.GetElement(i, j) - mat.GetElement(i, j));
			}
		}
		return neo;
	}
	else
		//������ �Ұ��� �� ��� ���ܸ� �߻���ŵ�ϴ�
		throw MATRIX_ERROR;
}
//����� �� ������ �����ϴ� ������ �Լ��Դϴ�
Matrix Matrix::operator *(Matrix& mat)
{
	//��ġ������ �������� Ȯ���մϴ�
	if (isValidTransposeOperation(mat))
	{
		//�����ϴٸ� ���ο� ����� �����մϴ�
		Matrix neo;
		//��ġ����� ��� ���ο� ũ���� �迭�� �����Ǳ� ������ ��Ģ�� ���� ����� ũ�⸦ �����մϴ�
		neo.ReserveBuffer(row, mat.col);
		for (int i = 0; i < neo.row; ++i)
		{
			for (int j = 0; j < neo.col; ++j)
			{
				int value = 0;
				//�� �����Ǵ� ������ ���� ���� �����մϴ�
				for (int k = 0; k < col; ++k)
				{					
					value += GetElement(i, k) * mat.GetElement(k, j);
				}
				//�ش� ���ҿ� �� ����� ���Ұ� ���� �Ҵ��մϴ�
				neo(i, j, value);
			}
		}
		return neo;
	}
	else
		//������ �Ұ��� �� ��� ���ܸ� �߻���ŵ�ϴ�
		throw MATRIX_ERROR;
}
//����� ���� �����ϴ� �Լ��Դϴ�
Matrix& Matrix::operator =(Matrix& mat)
{
	//���� ������ �������� Ȯ���մϴ�
	if (isValidNormalOperation(mat))
	{
		for (int i = 0; i < mat.row; ++i)
		{
			for (int j = 0; j < mat.col; ++j)
			{
				//������ ������ ��� �� �ش�Ǵ� ������ ���� �����մϴ�
				SetElement(i, j, mat.GetElement(i, j));
			}
		}
	}
	else
	{
		//���濬���� �Ұ����� ��� �Ű������� �־��� ����� ũ�⿡ �°� �޸𸮸� �ٽ� �Ҵ��մϴ�
		ReserveBuffer(mat.row, mat.col);
		//�Ű������� �־��� ����� ���� �ٽ� �����մϴ�
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