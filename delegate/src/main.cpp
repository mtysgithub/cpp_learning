#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "delegate.h"
using namespace std;

typedef int (global_f_signature)(int, int);						//这是定义一个顶层函数签名类型的等价命名符
typedef global_f_signature* global_f_pointer0;				//用函数签名的等价命名符定义一个函数指针类型

typedef int (*global_f_pointer1)(global_f_signature);	//这是定义一个顶层函数指针类型的等价命名符

int global_f_0(global_f_signature p)
{
	p (0, 0);
	return 0;
}

int global_f_1(int p1, int p2)
{
	return 0;
}

extern global_f_signature func_signature;		//声明一个 global_f_signature 签名样式的函数外链接

int main()
{
	global_f_pointer1 func_pointer = global_f_0;	//直接赋值一个顶层函数指针
	func_pointer (global_f_1);
	func_signature(0, 0);	//通过out link来匹配执行体

	DelegateHandle instance;
	DelegateHandle *instance_this = &instance;
	DelegateHandle::HandlerPointer member_func = &(DelegateHandle::handler);	//普通成员函数直接取代码段上的地址绑定到变量上
	//如何调用 ?
	(instance_this->*member_func)(0, 0);

	//模板技巧构造委托
	EventCenterType EventCenter(instance_this, &DelegateHandle::handler);
	EventCenter(0, 0);

	DelegateHandleExtend instance_extend;
	DelegateHandle *instanceEx_this = &instance_extend;
	EventCenterType EventCenter2(instanceEx_this, &DelegateHandle::handler);
	EventCenter2(1, 1);

	return 0;
}