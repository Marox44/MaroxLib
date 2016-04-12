#pragma once
#include <cstdint>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>
//#include <functional>


namespace Marox
{
	/// <summary>
	/// Threading tools
	/// </summary>
	namespace Threading
	{
		/// <summary>
		/// Creates the thread from a function.
		/// </summary>
		/// <param name="fn">Function that is supposed to work in a separated thread.</param>
		/// <param name="args">Arguments to the function.</param>
		/// <returns>A pointer to <c>std::thread</c> object.</returns>
		/// <example>
		/// #include <iostream>
		/// #include <MaroxLib\threads.hpp>
		/// 
		/// void RUN(int n)
		/// {
		/// 	while (1)
		/// 	{
		/// 		std::cout << "I'm a thread made from the function. And n = " << n << std::endl;
		/// 		Marox::Threading::THREAD::Sleep(500);
		/// 	}
		/// }
		/// 
		/// int main()
		/// {
		/// 	std::thread* t = Marox::Threading::CreateThreadFromFunction(RUN, 44);
		/// 
		///		//can be also e.g. anonymous function: std::thread* t = Marox::Threading::CreateThreadFromFunction([](int n)->void{while (1) { std::cout << "I'm a thread made from the function. And n = " << n << std::endl; Marox::Threading::THREAD::Sleep(500); }}, 44);
		/// 
		/// 	t->join();
		/// 
		/// 	return 0;
		/// }
		/// </example>
		template<typename Fn, typename... Args>
		static std::thread* CreateThreadFromFunction(Fn& fn, Args... args)
		{
			return (new std::thread(fn, args...));
		}
				void Sleep(unsigned int _ms)
				{
						std::this_thread::sleep_for(std::chrono::milliseconds(_ms));
				}

				unsigned int getNumberOfCores()
				{
						return std::thread::hardware_concurrency();
				}
		/// <summary>
		/// Provides interface for derived class making it able to run specified method in separated thread.
		/// </summary>
		/// <remarks>
		/// In order to give your class ability to run as a separated thread you have to inherit from <c>Marox::Threading::THREAD</c> and implement <c>void run()</c> method. Then you can use all the public methods.
		/// See example code below:
		/// </remarks>
		/// <example>
		/// <code>
		/// #include <iostream>
		/// #include <Windows.h>
		/// #include <MaroxLib\threads.hpp>
		/// 
		/// class Foo : public Marox::Threading::THREAD
		/// {
		/// public:
		/// 	Foo(){}
		/// 	~Foo(){}
		/// 
		/// private:
		/// 	void run() override
		/// 	{
		/// 		while (this->isThreadRunning())
		/// 		{
		/// 			 Marox::Threading::THREAD::Sleep(1000);
		/// 			std::cout << "Hi, I'm thread Foo and my ID is " << this->getID() << std::endl;
		/// 		}
		/// 	}
		/// };
		/// 
		/// class Boo : public Marox::Threading::THREAD
		/// {
		/// public:
		/// 	Boo(){}
		/// 	~Boo(){}
		/// 
		/// private:
		/// 	void run() override
		/// 	{
		/// 		while (this->isThreadRunning())
		/// 		{
		/// 			 Marox::Threading::THREAD::Sleep(1000);
		/// 			std::cout << "Hi, I'm thread Boo and my ID is " << this->getID() << std::endl << std::endl;
		/// 		}
		/// 	}
		/// };
		/// 
		/// int main()
		/// {
		/// 	Foo foo;
		/// 	Boo boo;
		/// 	foo.threadStart();
		/// 	boo.threadStart();
		/// 
		/// 	foo.join(); // join() one of the thread, so the main thread won't exit application
		/// 	return 0;
		/// }
		/// </code>
		/// The output from the code above is like:
		/// <code>
		/// Hi, I'm thread Foo and my ID is 1896
		///	Hi, I'm thread Boo and my ID is 6112
		///
		///	Hi, I'm thread Foo and my ID is 1896
		///	Hi, I'm thread Boo and my ID is 6112
		/// ...
		/// ...
		/// </code>
		/// </example>
		class THREAD
		{
		public:
			THREAD(const THREAD&) = delete;
			THREAD(THREAD&&) = delete;
			THREAD& operator=(const THREAD&) = delete;
			THREAD& operator=(THREAD&&) = delete;
			virtual ~THREAD() = default;
			/// <summary>
			/// Starts the thread.
			/// </summary>
			/// <param name="_join">If set to <c>true</c>, the thread will be started with <c>join</c></param>
			void threadStart(bool _join = false)
			{
				if (!this->is_thread_running)
				{
					this->is_thread_running = true;
					if (this->pRun)
					{
						T.swap(std::thread(THREAD::pRun));
					}
					else
					{
						T.swap(std::thread(&THREAD::run, this));
					}
					if (_join)
					{
						T.join();
					}
				}
			}
			/// <summary>
			/// Gives signal to finish thread loop execution.
			/// </summary>
			/// <remarks>
			/// Disables the <c>isThreadRunning</c> flag, so works only if you have e.g. <c>while (isThreadRunning())</c> loop inside your thread method.
			/// </remarks>
			void threadStop()
			{
				this->is_thread_running = false;
			}
			/// <summary>
			/// Returns the thread id.
			/// </summary>
			/// <returns>Thread id as <c>std::thread::id</c></returns>
			std::thread::id getID()
			{
				return this->T.get_id();
			}
			/// <summary>
			/// Checks whether the thread is running.
			/// </summary>
			/// <returns><c>true</c> if the thread is running, <c>false</c> if it is not</returns>
			bool isThreadRunning()
			{
				return this->is_thread_running;
			}
			/// <summary>
			/// Checks whether the thread is joinable.
			/// </summary>
			/// <remarks>
			/// (calls <c>std::thread::joinable()</c>)
			/// </remarks>
			/// <returns><c>true</c> if the thread is joinable</returns>
			bool isJoinable()
			{
				return this->T.joinable();
			}
			/// <summary>
			/// Method returns when the thread execution has completed. (calls <c>std::thread::join()</c>)
			/// </summary>
			/// <exception cref="std::exception">if the thread is not joinable</exception> 
			void join()
			{
				if (this->T.joinable())
				{
					this->T.join();
				}
				else
				{
					throw std::runtime_error("Thread is not joinable");
				}
			}

			/// <summary>
			/// Sleeps current thread.
			/// </summary>
			/// <remarks>
			/// Meant to be used from within the desired thread, thus inside <c>run()</c> method or inside the main thread.
			/// </remarks>
			/// <param name="_ms">duration [ms]</param>
			static void Sleep(unsigned int _ms)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(_ms));
			}

			static unsigned int getNumberOfCores()
			{
				return std::thread::hardware_concurrency();
			}

		protected:
			explicit THREAD() : is_thread_running(false), pRun(nullptr){}
			/// <summary>
			/// Main method of the thread - needs to be implemented in the derived class!
			/// </summary>
			/// <remarks>
			/// If your thread works as the e.g loop, you should check the state of <c>isThreadRunning</c> flag inside your method implementation. (see <c>THREAD</c> example code)
			/// </remarks>
			virtual void run() = 0;

		private:
			std::thread T;
			bool is_thread_running;
			void(*pRun)();
		};
	}
}
