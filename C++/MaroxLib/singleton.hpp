#pragma once

namespace Marox
{
	template<typename T>
	class Singleton final
	{
	public:
		Singleton() = delete;
		~Singleton() = delete;
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;

		template<typename... Args>
		static T* getInstance(Args... args);
		static void destroy();

	private:
		static T* m_instance;
	};

	template<typename T>
	typename T* Singleton<T>::m_instance = nullptr;


	template<typename T>
	template<typename... Args>
	T* Singleton<T>::getInstance(Args... args)
	{
		if (!m_instance)
		{
			Singleton<T>::m_instance = new T(args...);
		}

		return m_instance;
	}

	template<typename T>
	void Singleton<T>::destroy()
	{
		delete Singleton<T>::m_instance;
		Singleton<T>::m_instance = nullptr;
	}
}