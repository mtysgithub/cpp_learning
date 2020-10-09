#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace ASpace 
{
	class B
	{
	public:
		virtual void f(int) { std::cout << "B::f\n"; }
		void g(char) { std::cout << "B::g\n"; }
		void h(int) { std::cout << "B::h\n"; }

	protected:
		int m; // B::m is protected
		typedef int value_type;
	};
}

namespace BSpace
{
	using namespace ASpace;
	using B_Alias = B;

	class D : B_Alias
	{
	public:
		using B::m;										// D::m is public
		using B::value_type;							// D::value_type is public

		using B::f;
		void f(int) { std::cout << "D::f\n"; }		// D::f(int) overrides B::f(int)
		using B::g;
		void g(int) { std::cout << "D::g\n"; }	// both g(int) and g(char) are visible
																// as members of D
		using B::h;
		void h(int) { std::cout << "D::h\n"; }	// D::h(int) hides B::h(int)
	};
}

//Type alias, alias template (since C++11)
//https://en.cppreference.com/w/cpp/language/type_alias
template<typename T>
using memberf_pointer = void (T::*)(void);

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

	return 0;
}
