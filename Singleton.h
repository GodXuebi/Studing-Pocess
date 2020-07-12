#ifndef __SINGLETON__
#define __SINGLETON__


class Singleton
{
private:
	Singleton();
	Singleton(const Singleton&other);
public:
	static Singleton*GetInstance();
	static Singleton*instance;
	
}

Singleton*Singleton::instance = NULL;


//***************单线程安全***************
Singleton* Singleton::GetInstance()
{
	if(instance == NULL)
		instance =new Singleton();
	return instance;

}
//****************************************


//***************多线程安全,开销较大***************
Singleton* Singleton::GetInstance()
{
	Lock lock;
	if(instance == NULL)
		instance = new Singleton();
	return instance;

}
//************************************************


//***************双检查lock，多线程不安全********************
Singleton* Singleton::GetInstance()
{
	if(instance == NULL)
	{
		Lock lock;
		if(instance == NULL)
			instance = new Singleton();
	}
	return instance;

}
//*********************************************************


//***************多线程安全******************************
std::atomic<Singleton*> Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton* Singleton::GetInstance()
{
	Singleton*tmp = m_instance.load(std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_acquire);
	if(tmp == NULL)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		tmp = m_instance.load(std::memory_order_relaxed);
		if(tmp == NULL)
		{
			tmp = new Singleton();
			std::atomic_thread_fence(std::memory_order_release);
			m_instance.store(tmp,std::memory_order_relaxed);
		}
	}
	return tmp;
}
//*********************************************************


//*********************************************************
//Writen by myself
template<class T>
class Singleton
{
private:
	static std::mutex mtx;
	static T* volatile instance;
	Singleton(){}
	~Singleton();
	Singleton(const Singleton&other);
	Singleton&operator=(const Singleton&other);
public:
	T*getInstance()
	{
		if(!instance)
		{
			lock_guard<std::mutex> lock(mtx)
			if(!instance) 
			{
				instance = new T();
				atexit(Destroy);
			}
		}
	}
	
	void Destroy()
	{
		if(instance)
		{
			delete instance;	
		}
		return;
	}
};

template<class T>
std::mutex Singleton<T>::mtx;
T*Singleton<T>::instance == NULL;

#endif 


https://blog.csdn.net/qq_30968657/article/details/69261134?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase
