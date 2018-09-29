#pragma once
#include <memory>

using namespace std;

class A
{
public:
	A() {}
	virtual ~A() {}

	virtual const int get() = 0;
};
typedef shared_ptr<A> A_ptr;

class B : public A
{
public:
	B() {}
	virtual ~B() {}

	virtual void set(int value) = 0;
};
typedef shared_ptr<B> B_ptr;

class C : public B
{
	int value;

public:
	C() {}
	~C() {}

	const int get();
	void set(int value);
};
typedef shared_ptr<C> C_ptr;
