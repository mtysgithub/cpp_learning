#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "delegate.h"
using namespace std;

typedef int (global_f_signature)(int, int);						//���Ƕ���һ�����㺯��ǩ�����͵ĵȼ�������
typedef global_f_signature* global_f_pointer0;				//�ú���ǩ���ĵȼ�����������һ������ָ������

typedef int (*global_f_pointer1)(global_f_signature);	//���Ƕ���һ�����㺯��ָ�����͵ĵȼ�������

int global_f_0(global_f_signature p)
{
	p (0, 0);
	return 0;
}

int global_f_1(int p1, int p2)
{
	return 0;
}

extern global_f_signature func_signature;		//����һ�� global_f_signature ǩ����ʽ�ĺ���������

int main()
{
	global_f_pointer1 func_pointer = global_f_0;	//ֱ�Ӹ�ֵһ�����㺯��ָ��
	func_pointer (global_f_1);
	func_signature(0, 0);	//ͨ��out link��ƥ��ִ����

	DelegateHandle instance;
	DelegateHandle *instance_this = &instance;
	DelegateHandle::HandlerPointer member_func = &(DelegateHandle::handler);	//��ͨ��Ա����ֱ��ȡ������ϵĵ�ַ�󶨵�������
	//��ε��� ?
	(instance_this->*member_func)(0, 0);

	//ģ�弼�ɹ���ί��
	EventCenterType EventCenter(instance_this, &DelegateHandle::handler);
	EventCenter(0, 0);

	DelegateHandleExtend instance_extend;
	DelegateHandle *instanceEx_this = &instance_extend;
	EventCenterType EventCenter2(instanceEx_this, &DelegateHandle::handler);
	EventCenter2(1, 1);

	return 0;
}