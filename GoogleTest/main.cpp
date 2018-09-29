#include <iostream>
#include "gtest/gtest.h"
#include "smart_ptr.h"
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include "Matrix.h"

using namespace dvd;

#define AAA int zzz() { return 10; }
AAA;

using namespace std;

//bit field type
//각 비트를 이름으로 접근할 수 있다
struct {
	unsigned int carry : 1;
	unsigned int overflow : 1;
}psw;

class Furk
{
public:
	int i;
public:
	Furk(int a) { i = a; }
	~Furk() {}

	void Damn(shared_ptr<Furk> f)
	{
		cout << f.use_count() << endl;
	}
};


TEST(CONST_PRACTICE, CONST_PRACTICE)
{
	int a = 10;
	int const b = 11;

	const int * const c = &a;
	const int const * const d = &b;

	int * k = &a;

	//c = &b;
	//d = &a;
	*k = 30;
}

TEST(SMART_POINTER, SMART_POINTER)
{
	Furk * ffff = NULL;
	shared_ptr<Furk>* temp;
	shared_ptr<Furk>* temp2;
	shared_ptr<Furk>* temp3;
	{
		shared_ptr<Furk> fs(make_shared<Furk>(3));
		fs->i = 10;
		temp = &fs;
		temp2 = &fs;
		temp3 = &fs;
		{
			cout << fs << endl << (*temp)->i << endl;
			shared_ptr<Furk> mm(fs);
			{
				shared_ptr<Furk> nn(mm);

				cout << fs.use_count() << endl;

				mm->Damn(nn);

				cout << fs.use_count() << endl;
			}
			cout << fs.use_count() << endl;
		}
		cout << fs.use_count() << endl;
	}
	//여기 온 시점에서 카운팅이 0이 되서 메모리가 소멸되어야 할것 같은데 접근이 된다...-_-
	cout << (*temp) << endl << (*temp)->i;
}

TEST(VECTOR, VECTOR)
{
	vector<int> vec;

	vec.push_back(1);

	//순회
	zzz();

}


TEST(MAT_TEST, MAT_TEST)
{
	Matrix mat1(2, 3);
	Matrix mat2(3, 2);
	Matrix mat3(2, 3);

	mat1(0, 0, 2);
	mat1(0, 1, 2);
	mat1(0, 2, 2);
	mat1(1, 0, 2);
	mat1(1, 1, 2);
	mat1(1, 2, 2);
	
	mat2(0, 0, 2);
	mat2(0, 1, 2);
	mat2(1, 0, 2);
	mat2(1, 1, 2);
	mat2(2, 0, 2);
	mat2(2, 1, 2);
	
	mat3(0, 0, 2);
	mat3(0, 1, 2);
	mat3(0, 2, 2);
	mat3(1, 0, 2);
	mat3(1, 1, 2);
	mat3(1, 2, 2);

	Matrix mat4 = (mat1 + mat3) * mat2;
	Matrix mat5 = mat2 * (mat1 + mat3);

	for (int i = 0; i < mat4.getRow(); ++i)
	{
		for (int j = 0; j < mat4.getCol(); ++j)
		{
			cout << mat4(i, j) << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < mat5.getRow(); ++i)
	{
		for (int j = 0; j < mat5.getCol(); ++j)
		{
			cout << mat5(i, j) << " ";
		}
		cout << endl;
	}
}