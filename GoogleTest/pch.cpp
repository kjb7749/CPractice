//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"
using namespace std;


#pragma region FuncImpl
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////함수 구현부////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void bi_output_with_macro(int num)
{
	int size = sizeof(num) * 8;
	for (int i = 0; i < size; ++i)
	{
		printf("%d", BIT_INT(num, i) >> (size - i - 1));
	}
}

//이진 출력 함수
//매개변수로 정수형 num 을 받습니다
void bi_output(char* buffer, int num)
{
	unsigned int mask = 0x80000000;   //and 연산을 위한 마스크 변수
	int size = sizeof(num) * 8;      //총 비트의 크기를 구합니다 sizeof 함수로 시스템의 int의 크기를 구하고 바이트이므로 8비트를 곱합니다

	for (int i = 0; i < size; ++i)   //비트의 크기만큼 여기서는 4바이트 * 8비트 = 32 의 사이즈 만큼 반복합니다
	{
		buffer[i] = ((num & mask) >> (size - i - 1)) + '0';
		//printf("%d", ((num & mask) >> (size - i - 1)));      //num * mask 연산을 통해서 마스킹을 합니다. 이 경우 현재 마스크에 해당하는 비트만 남고 나머지는 0이 됩니다.
		//해댱되는 비트의 값을 그대로 출력하면 자리수에 따라서 2의 배수가,, 즉 1이 아닌 값들이 출력되므로 이를 모두 일괄적으로 1로 만들기 위해 >> 쉬프트 연산을 통해 1의 자리로 만든 후 출력합니다
		mask >>= 1;      //한 자리를 출력할때마다 마스크를 오른쪽으로 하나씩 옮겨야 하므로 mask의 값을 영구적으로 1 오른쪽 쉬프팅합니다.
	}
	buffer[size] = '\0';
}

//왼쪽으로 n 비트 이동하는 함수
//매개변수로 옮기고 싶은 변수 num과 쉬프팅 할 횟수 n을 받습니다
int lcshift(int num, int n)
{
	//n번 왼쪽으로 쉬프팅 해야하므로 n번 반복문을 수행합니다
	for (int i = 0; i < n; ++i)
	{
		//num의 가장 첫번째 비트값만 추출하기 위해 num과 0x80000000 == 1000...000 과 마스킹을 진행합니다 이 경우는 무조건 첫번째 비트만 추출됩니다!
		unsigned int firstBit = num & 0x80000000;
		//첫번째 비트를 가장 오른쪽에 옮겨야 하므로 31번(총 32비트인데 가장 첫번째 비트이므로 처음으로 옮겨야 하기 때문에 31번) 오른쪽으로 쉬프팅 합니다
		firstBit >>= 31;
		//num의 가장 첫번재 비트값을 firstBit 변수에 이미 저장 했으므로 가장 왼쪽에 있는 비트는 더 이상 필요가 없기 때문에 왼쪽 쉬프트 1번으로 소실시킵니다
		num <<= 1;
		//왼쪽으로 1번 쉬프팅 하게 되면 오른쪽이 0으로 패딩(쉬프트 연산으로 생긴 공백비트는 채우는 과정)되므로 그 빈칸을 firstBit로 채워넣습니다.
		// | (OR) 연산은 비트합과 같으므로 가장 오른쪽 비트 정보를 담고 있는 firstBit는 or 연산을 통해 num bit의 패딩된 데이터를 덮어 씌우게 됩니다.
		num |= 0x000000 | firstBit;
	}
	//이 반복문을 통해 변형된 num 정수값을 출력합니다
	return num;
}

//오른쪽으로 n 비트 이동하는 함수
//매개변수로 옮기고 싶은 변수 num과 쉬프팅 할 횟수 n을 받습니다
//모든 로직은 lcshift와 똑같습니다 다만 주의하셔야 할것은 저는 if 문을 활용해서 음수와 양수를 구별하지 않고 0x7fffffff 를 통해 가장 왼쪽의 비트를 소실시키고 거기에 OR 연산을 통해 수를 만들었습니다
int rcshift(int num, int n)
{
	for (int i = 0; i < n; ++i)
	{
		unsigned int lastBit = num & 0x00000001;
		lastBit <<= 31;
		num >>= 1;

		num = num & 0x7fffffff;
		num |= lastBit;
	}
	return num;
}


int mainInstead()
{
	//printf("\n");
	//bi_output(lcshift(-7, 10));
	//printf("\n");
	//bi_output(rcshift(5, 15));

	//누적된 값을 담기 위한 변수
	int accum = 0;
	char c;
	//개행 문자(\n)가 나올때까지 계속해서 문자를 하나씩 읽어옵니당
	while ((c = getchar()) != '\n')
	{
		//문자를 숫자로 바꿔요
		int num = c;
		//문자인 숫자가 수범위(0~9)내라면 0을 빼줘요
		if (c >= '0' && c <= '9')
		{
			num -= '0';
		}
		//문자인 숫자가 알파벳범위(a~f)내라면 a를 빼줘요
		else if (c >= 'a' && c <= 'f')
		{
			num = num - 'a' + 10;
		}
		//대문자도 똑같이 적용해줘요
		else if (c >= 'A' && c <= 'F')
		{
			num = num - 'A' + 10;
		}
		//이상한 문자열이 들어오면 계산이 불가능하니까 경고와 함께 종료시켜줘요
		else
		{
			printf("입력 문자열이 이상합니다. 프로그램을 종료합니다.\n");
			return 0;
		}
		//첫째 자리수부터 계속 누적시켜서 16을 곱해줘요!
		accum = accum * 16 + num;
	}
	//누적된 십진수 결과를 출력해요
	printf("%d\n", accum);
}


void imp(int *z)
{
	int a[] = { 0, 10, 20, 30, 40, 50 };
	int *p[] = { a, a + 1, a + 2, a + 3, a + 4 };
	int **pp = p;

	//2차원을 1차원으로 접근하는것은 불가능한가?
	int d[2][3][3] = { {{1,2,3},{4,5,6},{7,8,9}}, {{1,2,3},{4,5,6},{7,8,9} } };
	//int **p = &d[0];

	int r[3] = { 1,2,3 };


	for (int i = 0; i < 18; ++i)
	{
		printf("%d ", z[i]);
	}

	const char *c[] = { "ENTER", "NEW", "POINT", "FIRST" };
	const char **cp[] = { c + 3, c + 2, c + 1, c };
	const char ***cpp = cp;


	//FIRST, POINT
	   //cout << cpp << endl;
	   //cout << **cpp <<endl;      //두번참조해서 POINT 가 출력됨
	   //cout << cpp << endl;
	   //cout << **++cpp << endl;   //cpp 인덱스를 증가시켜(cp 배열에서 한자리 앞으로 가게 된다 이때 인덱스는 c+2 == c = c + 2) 참조한다. 그러므로 POINT가 찍히게 된다
	   //cout << cpp << endl;
	   //cout << ++**cpp << endl;   //cpp 를 두번 참조한 뒤(문자열까지 접근해서) 인덱스를 ++ 시킨다.. 문자열 하나를 앞으로 읽는다!
	   //cout << cpp << endl;

	   //cout << cpp << endl << **cpp << ++**cpp << endl << cpp << endl;
	   //printf("%s", **++cpp);
	   //printf("%s ", *--*cpp + 3);   //에러난다 -- 연산을 하려고 하지만 가장 앞을 나타내고 있기 때문에 스택 오버플로우가 일어난다
	   //printf("%s", *cpp[-2] + 3);   
	   //printf("%s\n", cpp[-1][-1] + 1);
}


char* revsqueeze(char* pStr, char c)
{
	char* temp;
	int i = 0, k;
	k = strlen(pStr);
	temp = (char*)malloc(k + 1);
	pStr = pStr + k - 1;      //가장 마지막 인덱스(널 문자바로 앞)로 갑니다
	int index = 0;
	for (index = 0, i = 0; i < k; ++i)
	{
		if (*(pStr - i) != c)
		{
			*(temp + index++) = *(pStr - i);
		}
	}
	*(temp + index) = '\0';
	return temp;
}

char* revsqueeze2(char* str, char c)
{
	const char checker = ' ';
	int i;
	int size = strlen(str);
	for (i = 0; i < strlen(str); ++i)
	{
		if (str[i] == c)
		{
			str[i] = checker;
			--size;
		}
	}
	char* resultStr = (char*)malloc(sizeof(char) * size + 1);      //+1은 널문자를 위한것

	resultStr[size] = '\0';
	int index = 0;
	for (int j = strlen(str) - 1; j >= 0; --j)
	{
		if (str[j] != checker)
			resultStr[index++] = str[j];
	}

	return resultStr;
}

int numcmp(const char* ps, const char* pt)
{
	float a, b;

	printf("numcmp called\n");

	a = atof(ps);
	b = atof(pt);

	if (a > b)
		return -1;
	else if (a < b)
		return 1;
	else
		return 0;

}


int fcmp(int(*ptr)(const char*, const char*), const char* ps, const char* pt)
{
	return ptr(ps, pt);
}


void q1(int argc, char* argv[])
{
	char str[256];
	int i = 0;
	printf("문자열을 입력하세요");
	while ((str[i++] = getchar()) != '\n');
	str[--i] = '\0';         //널 문자를 붙혀 문자열의 종점을 나타내줍니다
	printf("제거할 문자를 입력하세요");
	char c = getchar();

	char* nStr = revsqueeze(str, c);
	printf("%s", nStr);
	free(nStr);
}
void q2(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "인자수를 3개로 맞춰주세요" << endl;
		return;
	}
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);

	if (a + b >= strlen(argv[1]))
	{
		cout << "문자열의 길이를 초과합니다" <<endl;
		return;
	}
	mid(argv[1], a, b);
	cout << argv[1] << endl;
}
void q3(int argc, char* argv[])
{
}

void(*Problems[])(int, char*[]) = {
   q1,
   q2,
   q3
};


int getname(char* pname)
{
	int i = 0;
	char c;

	while (((c=getchar()) != '\n') && c != EOF)
	{
		*(pname + i++) = c;
	}
	if (c == '\n')
		*(pname + i) = '\0';
	if (c == EOF)
	{
		*pname = EOF;
	}
	return *pname;
}

struct node* addlist(struct node* p, char* w)
{
	if (p == NULL)
	{
		p = (struct node*)malloc(sizeof(struct node));
		p->name = namecopy(w);
		p->link = NULL;
	}
	else
	{
		p->link = addlist(p->link, w);
	}
	return p;
}

char* list2Str(struct node *p)
{
	int i = 0;
	char *pBuf = NULL;
	int size = 0;

	//문자열 길이 체크 동적 할당을 위해서
	struct node *t = p;
	while (t != NULL)
	{
		size += strlen(t->name);
		t = t->link;
	}
	
	pBuf = (char*)malloc(size+1);

	//본격적인 문자열 카피
	t = p;
	while (t != NULL)
	{
		strncpy(&pBuf[i], t->name, strlen(t->name));
		i += strlen(t->name);
		t = t->link;
	}
	pBuf[size] = '\0';

	return pBuf;
}

char* namecopy(char* s)
{
	char* p;
	p = (char*)malloc(strlen(s) + 1);
	strcpy(p, s);
	return p;
}

void listprint(struct node* p)
{
	while (p != NULL)
	{
		printf("%s\n", p->name);
		p = p->link;
	}
}


//재귀로는 구현하는게 불가능하다...ㅠㅠ, 최소 파라미터가 2개는 있어야 한다. 혹은 구조체에 변수를 추가하거나,, 그럼 의미가 1도 없다
struct node* invert(struct node* root)
{
	struct node *fir, *mid, *lat;
	
	fir = root;
	if (fir != NULL)
	{
		mid = fir->link;
		fir->link = NULL;
	}

	while (mid != NULL)
	{
		lat = mid->link;
		mid->link = fir;
		fir = mid;
		mid = lat;
	}

	return fir;
}

char *mid(char *str , int a, int b)
{
	for (int i = 0; i < b; ++i)
	{
		str[i] = str[a+i];
	}
	str[b] = '\0';
	return str;
}

void PrintResult(int value)
{
	if (value == 0)
		printf("실패\n");
	else
		printf("성공\n");
}

void StrBothEqual(char const * str1, char const * str2)
{
	PrintResult(!strcmp(str1, str2));
}

//문자열의 길이를 반환하는 함수입니다. 입력된 문자열의 길이를 반환합니다
int mystrlen(const char *pStr)
{
	//인덱스를 저장하 변수입니다
	int i = 0;
	//매개변수로 주어진 pStr부터 하나씩 확인하며 널문자(\0)가 나올때까지 인덱스를 증가시킵니다
	while (*(pStr + i) != '\0')
		++i;
	//계산된 인덱스, 즉 문자의 개수를 반환합니다
	return i;
}

//n개의 문자열이 같은지를 비교하는 함수입니다. 문자열이 상동이라면 0 그렇지 않다면 -1을 반환합니다
int mystrcmp(const char *pStr1, const char *pStr2, int size)
{
	//인덱스를 저장할 변수입니다
	int i = 0;
	//매개변수로 주어진 size 만큼 비교를 진행합니다
	while (i < size)
	{
		//만약 문자열이 같지 않다면 -1을 반환합니다
		if (*(pStr1 + i) != *(pStr2 + i))
		{
			return -1;
		}
		//반복문의 종료를 위해 인덱스를 지속적으로 증가시킵니다
		++i;
	}
	//모든 문자들이 상동일 경우 0을 반환합니다
	return 0;
}

int strcount(char *s, char *t)
{
	//검색 대상이 되는 문자열의 길이를 구합니다
	int length = mystrlen(s);
	//검색할 문자열의 길이를 구합니다
	int tLength = mystrlen(t);
	//개수를 저장할 변수를 선언합니다
	int count = 0;
	//인덱스를 저장하기 위한 변수를 선언합니다
	int i = 0;

	//만약 문자열의 길이가 0보다 짧다면 논리적으로 무한개가 되는 경우를 방지하기 위해 에외처리를 합니다
	if (tLength < 1)
		return 0;

	//전체 문자열 길이보다 현재까지 탐색한 문자열 + 탐색할 문자열의 길이보다 짧은 경우만 탐색을 진행합니다
	while(i + tLength <= length)
	{
		//검색할 문자열의 길이 만큼의 문자열을 검색 대상이 되는 문자열열과 비교하여 두 문자열이 같은 경우 count 변수를 증가시킵니다
		if (!mystrcmp(&s[i], t, tLength))
		{
			++count;
			//똑같은 문자열을 찾게 되면 그 문자열의 길이 만큼은 더 검색할 필요가 없기 때문에 인덱스 i를 검색할 문자열의 길이 만큼 증가시킵니다
			i += tLength;
		}
		else
		{
			//만약 검색할 문자열이 대상이 되는 문자열에서 검색되지 않으면 인덱스를 하나 증가시켜 다음 문자열에서 부터 비교하기 위해 인덱스를 하나 증가시킵니다
			++i;
		}
	}
	//검색된 문자열의 개수를 반환합니다
	return count;
}

//int strcount(char *ps, char  *pt)		//각 배열의 주소를 받아서 정수형으로 되돌려주는 함수
//{
//	char* pt_origin = pt;				//t배열의 처음 주소를 pt_origin 포인터변수로 선언하면서 값 입력
//	int Ls = strlen(ps);
//	int Lt = strlen(pt);				// s배열과 t배열의 길이 확인
//	int result = 0;						// s배열에서 일치하는 t 배열의 수
//	int f1 = 0, f2 = 0;
//
//	for (f1 = 0;;)						// 두번째 for 조건문 구동을 반복하기 위한 리셋에 사용
//
//	{
//		f2 = 0;							//	두번째 for문 구동을 위한 f2를 리셋
//
//		for (f2 = 0; (f2 < (Lt + 1)); f2++)
//		{
//			if (*ps == '\0') return result;		//s배열의 끝을 감지한 경우 함수 종료
//
//			else if (((*ps) == (*pt)) && (*(pt + 1) != '\0'))		// s배열과 t배열을 같은 값을 가지고 t배열의 다음 값이 문장의 종료가 아닌경우 포인터 이동
//			{
//				ps = ps + 1;
//				pt = pt + 1;
//			}
//
//			else if (((*ps) == (*pt)) && (*(pt + 1) == '\0'))		// s배열과 t배열이 같은 값을 가지고 t배열의 다음 값이 문장의 종료이면 결과값+1추가
//			{
//				pt = pt_origin;
//				ps = ps + 1;
//				result++;
//			}
//			else if (((*ps) == (*pt)) && (*(ps + 1) == (*(pt + 1))))		//s배열과 t배열이 같은 값이고 그 다음 배열의 값도 동일할때 포인터 이동
//			{
//				ps = ps + 1;
//				pt = pt + 1;
//			}
//			else {						// s배열과 t배열이 같지 않은 경우 포인터 이동 조건문 재실행 
//				ps = ps + 1;
//				pt = pt_origin;
//				break;
//			}
//
//		}
//	}
//
//	return result;
//
//}


#pragma endregion