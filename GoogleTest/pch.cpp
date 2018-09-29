//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"
using namespace std;


#pragma region FuncImpl
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////�Լ� ������////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void bi_output_with_macro(int num)
{
	int size = sizeof(num) * 8;
	for (int i = 0; i < size; ++i)
	{
		printf("%d", BIT_INT(num, i) >> (size - i - 1));
	}
}

//���� ��� �Լ�
//�Ű������� ������ num �� �޽��ϴ�
void bi_output(char* buffer, int num)
{
	unsigned int mask = 0x80000000;   //and ������ ���� ����ũ ����
	int size = sizeof(num) * 8;      //�� ��Ʈ�� ũ�⸦ ���մϴ� sizeof �Լ��� �ý����� int�� ũ�⸦ ���ϰ� ����Ʈ�̹Ƿ� 8��Ʈ�� ���մϴ�

	for (int i = 0; i < size; ++i)   //��Ʈ�� ũ�⸸ŭ ���⼭�� 4����Ʈ * 8��Ʈ = 32 �� ������ ��ŭ �ݺ��մϴ�
	{
		buffer[i] = ((num & mask) >> (size - i - 1)) + '0';
		//printf("%d", ((num & mask) >> (size - i - 1)));      //num * mask ������ ���ؼ� ����ŷ�� �մϴ�. �� ��� ���� ����ũ�� �ش��ϴ� ��Ʈ�� ���� �������� 0�� �˴ϴ�.
		//�؈ԵǴ� ��Ʈ�� ���� �״�� ����ϸ� �ڸ����� ���� 2�� �����,, �� 1�� �ƴ� ������ ��µǹǷ� �̸� ��� �ϰ������� 1�� ����� ���� >> ����Ʈ ������ ���� 1�� �ڸ��� ���� �� ����մϴ�
		mask >>= 1;      //�� �ڸ��� ����Ҷ����� ����ũ�� ���������� �ϳ��� �Űܾ� �ϹǷ� mask�� ���� ���������� 1 ������ �������մϴ�.
	}
	buffer[size] = '\0';
}

//�������� n ��Ʈ �̵��ϴ� �Լ�
//�Ű������� �ű�� ���� ���� num�� ������ �� Ƚ�� n�� �޽��ϴ�
int lcshift(int num, int n)
{
	//n�� �������� ������ �ؾ��ϹǷ� n�� �ݺ����� �����մϴ�
	for (int i = 0; i < n; ++i)
	{
		//num�� ���� ù��° ��Ʈ���� �����ϱ� ���� num�� 0x80000000 == 1000...000 �� ����ŷ�� �����մϴ� �� ���� ������ ù��° ��Ʈ�� ����˴ϴ�!
		unsigned int firstBit = num & 0x80000000;
		//ù��° ��Ʈ�� ���� �����ʿ� �Űܾ� �ϹǷ� 31��(�� 32��Ʈ�ε� ���� ù��° ��Ʈ�̹Ƿ� ó������ �Űܾ� �ϱ� ������ 31��) ���������� ������ �մϴ�
		firstBit >>= 31;
		//num�� ���� ù���� ��Ʈ���� firstBit ������ �̹� ���� �����Ƿ� ���� ���ʿ� �ִ� ��Ʈ�� �� �̻� �ʿ䰡 ���� ������ ���� ����Ʈ 1������ �ҽǽ�ŵ�ϴ�
		num <<= 1;
		//�������� 1�� ������ �ϰ� �Ǹ� �������� 0���� �е�(����Ʈ �������� ���� �����Ʈ�� ä��� ����)�ǹǷ� �� ��ĭ�� firstBit�� ä���ֽ��ϴ�.
		// | (OR) ������ ��Ʈ�հ� �����Ƿ� ���� ������ ��Ʈ ������ ��� �ִ� firstBit�� or ������ ���� num bit�� �е��� �����͸� ���� ����� �˴ϴ�.
		num |= 0x000000 | firstBit;
	}
	//�� �ݺ����� ���� ������ num �������� ����մϴ�
	return num;
}

//���������� n ��Ʈ �̵��ϴ� �Լ�
//�Ű������� �ű�� ���� ���� num�� ������ �� Ƚ�� n�� �޽��ϴ�
//��� ������ lcshift�� �Ȱ����ϴ� �ٸ� �����ϼž� �Ұ��� ���� if ���� Ȱ���ؼ� ������ ����� �������� �ʰ� 0x7fffffff �� ���� ���� ������ ��Ʈ�� �ҽǽ�Ű�� �ű⿡ OR ������ ���� ���� ��������ϴ�
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

	//������ ���� ��� ���� ����
	int accum = 0;
	char c;
	//���� ����(\n)�� ���ö����� ����ؼ� ���ڸ� �ϳ��� �о�ɴϴ�
	while ((c = getchar()) != '\n')
	{
		//���ڸ� ���ڷ� �ٲ��
		int num = c;
		//������ ���ڰ� ������(0~9)����� 0�� �����
		if (c >= '0' && c <= '9')
		{
			num -= '0';
		}
		//������ ���ڰ� ���ĺ�����(a~f)����� a�� �����
		else if (c >= 'a' && c <= 'f')
		{
			num = num - 'a' + 10;
		}
		//�빮�ڵ� �Ȱ��� ���������
		else if (c >= 'A' && c <= 'F')
		{
			num = num - 'A' + 10;
		}
		//�̻��� ���ڿ��� ������ ����� �Ұ����ϴϱ� ���� �Բ� ����������
		else
		{
			printf("�Է� ���ڿ��� �̻��մϴ�. ���α׷��� �����մϴ�.\n");
			return 0;
		}
		//ù° �ڸ������� ��� �������Ѽ� 16�� �������!
		accum = accum * 16 + num;
	}
	//������ ������ ����� ����ؿ�
	printf("%d\n", accum);
}


void imp(int *z)
{
	int a[] = { 0, 10, 20, 30, 40, 50 };
	int *p[] = { a, a + 1, a + 2, a + 3, a + 4 };
	int **pp = p;

	//2������ 1�������� �����ϴ°��� �Ұ����Ѱ�?
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
	   //cout << **cpp <<endl;      //�ι������ؼ� POINT �� ��µ�
	   //cout << cpp << endl;
	   //cout << **++cpp << endl;   //cpp �ε����� ��������(cp �迭���� ���ڸ� ������ ���� �ȴ� �̶� �ε����� c+2 == c = c + 2) �����Ѵ�. �׷��Ƿ� POINT�� ������ �ȴ�
	   //cout << cpp << endl;
	   //cout << ++**cpp << endl;   //cpp �� �ι� ������ ��(���ڿ����� �����ؼ�) �ε����� ++ ��Ų��.. ���ڿ� �ϳ��� ������ �д´�!
	   //cout << cpp << endl;

	   //cout << cpp << endl << **cpp << ++**cpp << endl << cpp << endl;
	   //printf("%s", **++cpp);
	   //printf("%s ", *--*cpp + 3);   //�������� -- ������ �Ϸ��� ������ ���� ���� ��Ÿ���� �ֱ� ������ ���� �����÷ο찡 �Ͼ��
	   //printf("%s", *cpp[-2] + 3);   
	   //printf("%s\n", cpp[-1][-1] + 1);
}


char* revsqueeze(char* pStr, char c)
{
	char* temp;
	int i = 0, k;
	k = strlen(pStr);
	temp = (char*)malloc(k + 1);
	pStr = pStr + k - 1;      //���� ������ �ε���(�� ���ڹٷ� ��)�� ���ϴ�
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
	char* resultStr = (char*)malloc(sizeof(char) * size + 1);      //+1�� �ι��ڸ� ���Ѱ�

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
	printf("���ڿ��� �Է��ϼ���");
	while ((str[i++] = getchar()) != '\n');
	str[--i] = '\0';         //�� ���ڸ� ���� ���ڿ��� ������ ��Ÿ���ݴϴ�
	printf("������ ���ڸ� �Է��ϼ���");
	char c = getchar();

	char* nStr = revsqueeze(str, c);
	printf("%s", nStr);
	free(nStr);
}
void q2(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "���ڼ��� 3���� �����ּ���" << endl;
		return;
	}
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);

	if (a + b >= strlen(argv[1]))
	{
		cout << "���ڿ��� ���̸� �ʰ��մϴ�" <<endl;
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

	//���ڿ� ���� üũ ���� �Ҵ��� ���ؼ�
	struct node *t = p;
	while (t != NULL)
	{
		size += strlen(t->name);
		t = t->link;
	}
	
	pBuf = (char*)malloc(size+1);

	//�������� ���ڿ� ī��
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


//��ͷδ� �����ϴ°� �Ұ����ϴ�...�Ф�, �ּ� �Ķ���Ͱ� 2���� �־�� �Ѵ�. Ȥ�� ����ü�� ������ �߰��ϰų�,, �׷� �ǹ̰� 1�� ����
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
		printf("����\n");
	else
		printf("����\n");
}

void StrBothEqual(char const * str1, char const * str2)
{
	PrintResult(!strcmp(str1, str2));
}

//���ڿ��� ���̸� ��ȯ�ϴ� �Լ��Դϴ�. �Էµ� ���ڿ��� ���̸� ��ȯ�մϴ�
int mystrlen(const char *pStr)
{
	//�ε����� ������ �����Դϴ�
	int i = 0;
	//�Ű������� �־��� pStr���� �ϳ��� Ȯ���ϸ� �ι���(\0)�� ���ö����� �ε����� ������ŵ�ϴ�
	while (*(pStr + i) != '\0')
		++i;
	//���� �ε���, �� ������ ������ ��ȯ�մϴ�
	return i;
}

//n���� ���ڿ��� �������� ���ϴ� �Լ��Դϴ�. ���ڿ��� ���̶�� 0 �׷��� �ʴٸ� -1�� ��ȯ�մϴ�
int mystrcmp(const char *pStr1, const char *pStr2, int size)
{
	//�ε����� ������ �����Դϴ�
	int i = 0;
	//�Ű������� �־��� size ��ŭ �񱳸� �����մϴ�
	while (i < size)
	{
		//���� ���ڿ��� ���� �ʴٸ� -1�� ��ȯ�մϴ�
		if (*(pStr1 + i) != *(pStr2 + i))
		{
			return -1;
		}
		//�ݺ����� ���Ḧ ���� �ε����� ���������� ������ŵ�ϴ�
		++i;
	}
	//��� ���ڵ��� ���� ��� 0�� ��ȯ�մϴ�
	return 0;
}

int strcount(char *s, char *t)
{
	//�˻� ����� �Ǵ� ���ڿ��� ���̸� ���մϴ�
	int length = mystrlen(s);
	//�˻��� ���ڿ��� ���̸� ���մϴ�
	int tLength = mystrlen(t);
	//������ ������ ������ �����մϴ�
	int count = 0;
	//�ε����� �����ϱ� ���� ������ �����մϴ�
	int i = 0;

	//���� ���ڿ��� ���̰� 0���� ª�ٸ� �������� ���Ѱ��� �Ǵ� ��츦 �����ϱ� ���� ����ó���� �մϴ�
	if (tLength < 1)
		return 0;

	//��ü ���ڿ� ���̺��� ������� Ž���� ���ڿ� + Ž���� ���ڿ��� ���̺��� ª�� ��츸 Ž���� �����մϴ�
	while(i + tLength <= length)
	{
		//�˻��� ���ڿ��� ���� ��ŭ�� ���ڿ��� �˻� ����� �Ǵ� ���ڿ����� ���Ͽ� �� ���ڿ��� ���� ��� count ������ ������ŵ�ϴ�
		if (!mystrcmp(&s[i], t, tLength))
		{
			++count;
			//�Ȱ��� ���ڿ��� ã�� �Ǹ� �� ���ڿ��� ���� ��ŭ�� �� �˻��� �ʿ䰡 ���� ������ �ε��� i�� �˻��� ���ڿ��� ���� ��ŭ ������ŵ�ϴ�
			i += tLength;
		}
		else
		{
			//���� �˻��� ���ڿ��� ����� �Ǵ� ���ڿ����� �˻����� ������ �ε����� �ϳ� �������� ���� ���ڿ����� ���� ���ϱ� ���� �ε����� �ϳ� ������ŵ�ϴ�
			++i;
		}
	}
	//�˻��� ���ڿ��� ������ ��ȯ�մϴ�
	return count;
}

//int strcount(char *ps, char  *pt)		//�� �迭�� �ּҸ� �޾Ƽ� ���������� �ǵ����ִ� �Լ�
//{
//	char* pt_origin = pt;				//t�迭�� ó�� �ּҸ� pt_origin �����ͺ����� �����ϸ鼭 �� �Է�
//	int Ls = strlen(ps);
//	int Lt = strlen(pt);				// s�迭�� t�迭�� ���� Ȯ��
//	int result = 0;						// s�迭���� ��ġ�ϴ� t �迭�� ��
//	int f1 = 0, f2 = 0;
//
//	for (f1 = 0;;)						// �ι�° for ���ǹ� ������ �ݺ��ϱ� ���� ���¿� ���
//
//	{
//		f2 = 0;							//	�ι�° for�� ������ ���� f2�� ����
//
//		for (f2 = 0; (f2 < (Lt + 1)); f2++)
//		{
//			if (*ps == '\0') return result;		//s�迭�� ���� ������ ��� �Լ� ����
//
//			else if (((*ps) == (*pt)) && (*(pt + 1) != '\0'))		// s�迭�� t�迭�� ���� ���� ������ t�迭�� ���� ���� ������ ���ᰡ �ƴѰ�� ������ �̵�
//			{
//				ps = ps + 1;
//				pt = pt + 1;
//			}
//
//			else if (((*ps) == (*pt)) && (*(pt + 1) == '\0'))		// s�迭�� t�迭�� ���� ���� ������ t�迭�� ���� ���� ������ �����̸� �����+1�߰�
//			{
//				pt = pt_origin;
//				ps = ps + 1;
//				result++;
//			}
//			else if (((*ps) == (*pt)) && (*(ps + 1) == (*(pt + 1))))		//s�迭�� t�迭�� ���� ���̰� �� ���� �迭�� ���� �����Ҷ� ������ �̵�
//			{
//				ps = ps + 1;
//				pt = pt + 1;
//			}
//			else {						// s�迭�� t�迭�� ���� ���� ��� ������ �̵� ���ǹ� ����� 
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