#include <iostream>
#include <vector>
using namespace std;

//The Function Pointer Tutorials
//http://www.newty.de/fpt/index.html

template<typename TReturn, typename ...TArgs>
class Delegate
{
public:
	typedef Delegate<TReturn, TArgs...> DelegateType;		//定义特化后的等价命名符
	typedef TReturn return_type;

public:
	class IBaseFunction
	{
	public:
		virtual return_type operator() (TArgs... args) = 0;
	};

	template <typename TClass>
	class MemberFunction : public IBaseFunction
	{
	public:
		typedef TClass class_type;
		typedef return_type(class_type::*function_type)(TArgs...);		//这一步,按照外层 Delegate 特化的规格，我们约束出一个符合规格的成员函数指针类型 function_type

		explicit MemberFunction(class_type *_this, function_type func)
		{
			m_instance = _this;
			m_memFunction = func;
		}

		return_type operator() (TArgs... args) override
		{
			return (m_instance->*m_memFunction)(args...);		//args必须带上... 才能unpack
		}

	private:
		class_type *m_instance;
		function_type m_memFunction;
	};
	
public:
	Delegate() = delete;

	//warning C4346: “Delegate<TReturn,TArgs...>::MemberFunction<TClass>::function_type”: 依赖名称不是类型
	//用“typename”为前缀来表示类型
	template<typename TClass>
	explicit Delegate(TClass *_this, typename MemberFunction<TClass>::function_type func)		//第二段形参上必须用 typename 导出一个等价的符号给编译器修饰为形参的数据类型
	{
		m_func = new MemberFunction<TClass>(_this, func);
	}

	~Delegate()
	{
		delete m_func;
	}

	TReturn operator() (TArgs... args)
	{
		return (*m_func)(args...);
	}

private:
	//由于我们不希望在Delegate的定义上暴露TClass，而只在构造函数局部上插入一个带TClass的function_type, 所以必须要有一个基类型脱去这个符号
	//MemberFunction<TClass> m_func;		

	IBaseFunction *m_func;
};

class DelegateHandle
{
public:
	using HandlerSignature = int (DelegateHandle::*) (int, int);
	using HandlerPointer = int (DelegateHandle::*)(int, int);

	int handler_outthere (int a, int b);

	int handler(int a, int b)	//我们想办法把这个handler 绑到一个Delegate
	{
		//如果我们确实希望handle虚函数回调，应该自己手动约定触发
		this->virtual_handler(a, b);

		return 0;
	}

	virtual int virtual_handler(int a, int b)		//如果是一个虚函数,该如何处理?
	{
		cout << a << " " << b << endl;
		return 0;
	}
};

class DelegateHandleExtend : public DelegateHandle
{
public:
	virtual int virtual_handler(int a, int b) override
	{
		cout << "virtual_handler " <<  a << " " << b << endl;
		return 0;
	}
};

extern DelegateHandle::HandlerSignature handler_outthere;
using EventCenterType = Delegate<int, int, int>;

int DelegateHandle::handler_outthere(int a, int b)
{
	cout << "handler_outthere " << a << " " << b << endl;
	return 0;
}