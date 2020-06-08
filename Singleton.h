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
		instance =n ew Singleton();
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
#endif 
