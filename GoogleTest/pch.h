#pragma once
#include "gtest/gtest.h"
#include <stdlib.h>

#define BIT_INT(num, index) (((num) & (0x80000000 >> (index))))

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////구조체 선언부////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
struct node {
	char* name;
	struct node* link;
};

#pragma region FuncDef
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////함수 선언부/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void(*Problems[])(int, char*[]);
void q1(int argc, char* argv[]);
void q2(int argc, char* argv[]);
void q3(int argc, char* argv[]);

void bi_output_with_macro(int num);
void bi_output(char* buffer, int num);
int lcshift(int num, int n);
int rcshift(int num, int n);
void imp(int *z);
char* revsqueeze(char* str, char c);
char* revsqueeze2(char* str, char c);
int mainInstead();

int fcmp(int(*ptr)(const char*, const char*), const char*, const char*);


int getname(char*);
struct node* addlist(struct node*, char*);
char* namecopy(char*);
void listprint(struct node*);
struct node* invert(struct node*);
char* list2Str(struct node *);

char *mid(char*, int, int);


int strcount(char *s, char *t);

#pragma endregion