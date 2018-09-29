#include "pch.h"
#define MAX_BUF_SIZE 256
#include <stdlib.h>

//걱정되는점 2가지
//1. 일반파일을 입력받을때 아무것도 없는 빈 파일이라도 생성시켜줘야 하나요?
//2. MAX_BUF_SIZE를 초과하는 크기의 데이터가 들어 왔을때는 입력된 데이터 일부가 소실될 것 같은데 이를 회피할 다른 방법이 있나요?


//#if _DEBUG
char InputforTest[MAX_BUF_SIZE];
char OutputforTest[MAX_BUF_SIZE];
//#endif;

int fakemain(int argc, char *argv[])
{
	char buf[MAX_BUF_SIZE];
	char c;
	int i = 0;
	FILE *fp;

	if (argc == 1)
	{
		i = 0;
		while ((buf[i++] = getc(stdin)) != EOF);
		//buf[--i] = '\0';

		strcpy(InputforTest, buf);

		i = 0;
		while (buf[i] != EOF)
		{
			putc(buf[i++], stdout);
		}
	}
	else if (argc == 2)
	{
		i = 0;
		fp = fopen(argv[1], "rt");
		if (fp == NULL)
			exit(2);
		while ((buf[i++] = getc(fp)) != EOF);
		fclose(fp);
		//buf[--i] = '\0';

		i = 0;
		while (buf[i] != EOF)
		{
			putc(buf[i], stdout);
//#if _DEBUG
			OutputforTest[i] = buf[i];
//#endif;
			++i;
		}
	}
	else if (argc == 3)
	{
		if (!strcmp(argv[1], "@"))
		{
			while ((buf[i++] = getc(stdin)) != EOF);
			fp = fopen(argv[2], "wt+");
			if (fp == NULL)
				exit(1);

			i = 0;
			while (buf[i] != EOF)
			{
				fputc(buf[i], fp);
				InputforTest[i] = buf[i];
				++i;
			}
			fclose(fp);
		}
		else
		{
			i = 0;
			fp = fopen(argv[1], "rt");
			if (fp == NULL)
				exit(2);
			while ((buf[i++] = getc(fp)) != EOF);
			fclose(fp);

			i = 0;
			fp = fopen(argv[2], "wt+");
			if (fp == NULL)
				exit(3);
			while (buf[i] != EOF)
			{
				putc(buf[i], fp);
				++i;
			}
			fclose(fp);
		}
	}
	else
	{
		puts("인수의 입력이 잘못되었습니다");
	}
	return 0;
}

//TEST(FILEIO_PARAM1, FILEIO_PARAM1)
//{
//	memset(InputforTest, NULL, sizeof(InputforTest));
//	memset(OutputforTest, NULL, sizeof(OutputforTest));
//
//	int argc = 1;
//	char *argv[] = {"frw.exe"};
//	fakemain(argc, argv);
//
//	EXPECT_STREQ(InputforTest, OutputforTest);
//}

//TEST(FILEIO_PARAM3_S2F, FILEIO_PARAM3_S2F)
//{
//	memset(InputforTest, NULL, sizeof(InputforTest));
//	memset(OutputforTest, NULL, sizeof(OutputforTest));
//
//	int argc = 3;
//	char *argv[] = { "frw.exe", "@", "test.txt" };
//	fakemain(argc, argv);
//
//	FILE *fp = fopen(argv[2], "rt");
//	fread(OutputforTest, sizeof(char), MAX_BUF_SIZE, fp);
//	fclose(fp);
//
//	//EOF 파일은 문자열 체크에 사용될 수 없기 때문에 EOF를 "\0"로 치환한다
//	/*char* eofchar = strchr(InputforTest, EOF);
//	memcpy(eofchar, "\0", 1);*/
//
//	EXPECT_STREQ(InputforTest, OutputforTest);
//}
//
//TEST(FILEIO_PARAM2, FILEIO_PARAM2)
//{
//	memset(InputforTest, NULL, sizeof(InputforTest));
//	memset(OutputforTest, NULL, sizeof(OutputforTest));
//
//	int argc = 2;
//	char *argv[] = { "frw.exe", "test.txt" };
//
//	FILE *fp = fopen(argv[1], "rt");
//	fread(InputforTest, sizeof(char), MAX_BUF_SIZE, fp);
//	fclose(fp);
//
//	fakemain(argc, argv);
//
//	EXPECT_STREQ(InputforTest, OutputforTest);
//}
//
//TEST(FILEIO_PARAM3_F2F, FILEIO_PARAM3_F2F)
//{
//	memset(InputforTest, NULL, sizeof(InputforTest));
//	memset(OutputforTest, NULL, sizeof(OutputforTest));
//
//	int argc = 3;
//	char *argv[] = { "frw.exe", "test.txt", "test2.txt" };
//	fakemain(argc, argv);
//
//	FILE *fp = fopen(argv[1], "rt");
//	fread(InputforTest, sizeof(char), MAX_BUF_SIZE, fp);
//	fclose(fp);
//
//	fp = fopen(argv[2], "rt");
//	fread(OutputforTest, sizeof(char), MAX_BUF_SIZE, fp);
//	fclose(fp);
//
//
//	/*char* eofchar = strchr(OutputforTest, EOF);
//	memcpy(eofchar, "\0", 1);*/
//
//	EXPECT_STREQ(InputforTest, OutputforTest);
//}





TEST(STRCOUNT, STRCOUNT)
{
	EXPECT_EQ(strcount("strstrstr", "str"), 3);
	EXPECT_EQ(strcount("strstrstr", "st"), 3);
	EXPECT_EQ(strcount("strrrrstr", "r"), 5);
	EXPECT_EQ(strcount("strstrstr", "a"), 0);
	EXPECT_EQ(strcount("str", "str"), 1);
	EXPECT_EQ(strcount("st", "str"), 0);
	EXPECT_EQ(strcount("strs", "str"), 1);
	EXPECT_EQ(strcount("strs", ""), 0);
}

//
//int main(int argc, char *argv[])
//{
//	fakemain(argc, argv);
//	return 0;
//}