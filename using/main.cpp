#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace ASpace 
{
	class B
	{
	public:
		class BInternal;

	public:
		virtual void f(int) { std::cout << "B::f\n"; }
		void g(char) { std::cout << "B::g\n"; }
		void h(int) { std::cout << "B::h\n"; }

	protected:
		int m; // B::m is protected
		using value_type = int;
	};
}

namespace BSpace
{
	using B_Alias = ASpace::B;

	class D : public B_Alias
	{
	public:
		using B::m;										// D::m is public
		using B::value_type;

		using B::f;
		void f(int) { std::cout << "D::f\n"; }		// D::f(int) overrides B::f(int)
		using B::g;
		void g(int) { std::cout << "D::g\n"; }	// both g(int) and g(char) are visible
																// as members of D
		using B::h;
		void h(int) { std::cout << "D::h\n"; }	// D::h(int) hides B::h(int)
	};
}
//-----------------------------------------------------------------------------------

//Type alias, alias template (since C++11)
//https://en.cppreference.com/w/cpp/language/type_alias
template<typename T>
using memberf_pointer = void (T::*)(void);

//模板套模板 (since C++14)
template<typename T>
using vec_member_pointer = std::vector<memberf_pointer<typename T::BInternal>>;

//-----------------------------------------------------------------------------------

//模板的 specializing 必须是有穷展开
template<class T>
struct A;
template<class T>
using B = typename A<T>::U; // type-id is A<T>::U

template<class T>
struct A 
{
	struct AInternal;
	typedef B<T> U;
};
//B<int> b; //error

//-----------------------------------------------------------------------------------

int main()
{
	//using token features :

	//1. using - directives
	//2.using - declarations namespace members
	//3.using-declarations class members
	//4.type alias 
	//5.alias template declarations

	//using - declarations
	//https://en.cppreference.com/w/cpp/language/using_declaration

	//using - declarations namespace members
	using BSpace::D;
	D d;
	d.m = 1;

	vec_member_pointer<D> vec_d_pointer;

	return 0;
}
