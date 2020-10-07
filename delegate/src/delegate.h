#include <iostream>
#include <vector>
using namespace std;

//The Function Pointer Tutorials
//http://www.newty.de/fpt/index.html

template<typename TReturn, typename ...TArgs>
class Delegate
{
public:
	typedef Delegate<TReturn, TArgs...> DelegateType;		//�����ػ���ĵȼ�������
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
		typedef return_type(class_type::*function_type)(TArgs...);		//��һ��,������� Delegate �ػ��Ĺ������Լ����һ�����Ϲ��ĳ�Ա����ָ������ function_type

		explicit MemberFunction(class_type *_this, function_type func)
		{
			m_instance = _this;
			m_memFunction = func;
		}

		return_type operator() (TArgs... args) override
		{
			return (m_instance->*m_memFunction)(args...);		//args�������... ����unpack
		}

	private:
		class_type *m_instance;
		function_type m_memFunction;
	};
	
public:
	Delegate() = delete;

	//warning C4346: ��Delegate<TReturn,TArgs...>::MemberFunction<TClass>::function_type��: �������Ʋ�������
	//�á�typename��Ϊǰ׺����ʾ����
	template<typename TClass>
	explicit Delegate(TClass *_this, typename MemberFunction<TClass>::function_type func)		//�ڶ����β��ϱ����� typename ����һ���ȼ۵ķ��Ÿ�����������Ϊ�βε���������
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
	//�������ǲ�ϣ����Delegate�Ķ����ϱ�¶TClass����ֻ�ڹ��캯���ֲ��ϲ���һ����TClass��function_type, ���Ա���Ҫ��һ����������ȥ�������
	//MemberFunction<TClass> m_func;		

	IBaseFunction *m_func;
};

class DelegateHandle
{
public:
	using HandlerSignature = int (DelegateHandle::*) (int, int);
	using HandlerPointer = int (DelegateHandle::*)(int, int);

	int handler_outthere (int a, int b);

	int handler(int a, int b)	//������취�����handler ��һ��Delegate
	{
		//�������ȷʵϣ��handle�麯���ص���Ӧ���Լ��ֶ�Լ������
		this->virtual_handler(a, b);

		return 0;
	}

	virtual int virtual_handler(int a, int b)		//�����һ���麯��,����δ���?
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