#include "stdafx.h"
#include "CppUnitTest.h"


#include "..\MaroxLib\all.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



struct dog
{
	dog() = default;
	~dog() = default;

	int age = 5;
	const std::string name = "Azor";
};

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<struct dog>(struct dog* d)
			{
				//return Marox::Tools::Convert::string_to_wstring(d.name);
				RETURN_WIDE_STRING(d);
			}
			template<>
			static std::wstring ToString<struct dog>(const struct dog& d)
			{
				return Marox::Tools::Convert::string_to_wstring(d.name);
				//RETURN_WIDE_STRING(d);
			}

			template<>
			static std::wstring ToString<struct Marox::Tools::FileVersionInfo>(const struct Marox::Tools::FileVersionInfo& fvi)
			{
				return Marox::Tools::Convert::string_to_wstring(((struct Marox::Tools::FileVersionInfo)fvi).ToString());
				//RETURN_WIDE_STRING(d);
			}
		}
	}
}

namespace CPP_UNIT_TESTS
{
	TEST_CLASS(Random)
	{
	public:

		TEST_METHOD(rand_int)
		{
			std::vector<int> numbers;
			for (size_t i = 0; i < 1000; i++)
			{
				numbers.push_back(Marox::Tools::Random::rand(1, 100));
			}
			bool range = true;
			bool type = true;
			for (const auto& i : numbers)
			{
				if (!(i >= 1 && i <= 100))
				{
					range = false;
				}
				if (std::floor(i) != i)
				{
					type = false;
				}
			}

			Assert::IsTrue(range, L"range error");
			Assert::IsTrue(type, L"type error");
		}

		TEST_METHOD(rand_double)
		{
			std::vector<double> numbers;
			for (size_t i = 0; i < 1000; i++)
			{
				numbers.push_back(Marox::Tools::Random::rand(1.0, 2.0));
			}
			bool range = true;
			bool type = true;
			for (const auto& i : numbers)
			{
				if (!(i >= 1 && i <= 2))
				{
					range = false;
				}
			}

			Assert::IsTrue(range, L"range error");
		}

		TEST_METHOD(randomize_collection)
		{
			std::vector<int> values = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			int values2[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			Marox::Tools::Random::randomizeCollection(values);
			Marox::Tools::Random::randomizeCollection(values2);

			int sum = 0;
			for (const auto& i : values)
			{
				sum += i;
			}
			for (const auto& i : values2)
			{
				sum += i;
			}

			Assert::AreEqual(sum, 45 * 2, L"sum error");
		}

	};

	TEST_CLASS(Singleton)
	{
	public:
		TEST_METHOD(singleton_1)
		{
			int* a = Marox::Singleton<int>::getInstance();
			auto b = a;
			auto c = Marox::Singleton<int>::getInstance();
			int d = *(Marox::Singleton<int>::getInstance());
			int e = *a;

			Assert::AreEqual(a, b, L"1");
			Assert::AreEqual(b, c, L"2");
			Assert::AreEqual(*c, d, L"3");
			Assert::AreEqual(*c, d, L"4");
			Assert::AreEqual(*a, d, L"8");
			Assert::AreEqual(*a, e, L"9");

			Assert::AreSame(*a, *b, L"5");
			Assert::AreSame(*b, *c, L"6");
			Assert::AreSame(*c, *a, L"7");
		}

		TEST_METHOD(singleton_2)
		{
			dog* a = Marox::Singleton<dog>::getInstance();
			dog* b = Marox::Singleton<dog>::getInstance();

			Assert::AreEqual(a, b, L"1");
			Assert::AreSame(*a, *b, L"2");
		}
	};

	TEST_CLASS(Time)
	{
	public:
		TEST_METHOD(timers_1)
		{
			Marox::Tools::Timer t1 = Marox::Tools::Timer();

			std::vector<double> data;
			for (size_t i = 0; i < 1000; i++)
			{
				data.push_back(Marox::Tools::Random::rand(1.0, 10.0));
			}

			Marox::Tools::Timer t2 = Marox::Tools::Timer();

			auto time = Marox::Tools::Timer::getDuration_milliseconds(t1, t2);
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(std::to_string((int)time).c_str());

			Assert::IsTrue((time <= INT_MAX && time > 0), L"1");
		}
	};

	TEST_CLASS(md5)
	{
	public:
		TEST_METHOD(md5_string)
		{
			//
			auto m1 = Marox::Tools::MD5::hashString("Ala ma kota");
			std::string _s1 = "Ala ma kota";
			auto m2 = Marox::Tools::MD5::hashString(_s1.c_str());
			auto m3 = Marox::Tools::MD5::hashMemory((BYTE*)_s1.c_str(), _s1.length());

			//
			auto _f = Marox::Tools::getTemporaryFile();
			std::fstream file = std::fstream(_f);
			file << "Ala ma kota";
			file.close();

			auto m4 = Marox::Tools::MD5::hashFile(_f);


			Assert::AreEqual(m1, m2, L"1");
			Assert::AreEqual(m2, m3, L"2");
			Assert::AreEqual(m3, m4, L"3");
		}
	};

	TEST_CLASS(http)
	{
	public:
		TEST_METHOD(http_get_1)
		{
			auto res1 = Marox::HTTP::GET("http://httpbin.org/user-agent");
			auto result1 = res1.content.find("WinHttpClient");

			Assert::IsTrue((result1 != std::string::npos), L"1");
		}

		TEST_METHOD(http_post_1)
		{
			std::map<std::string, std::string> data = { { "name", "Marek" }, { "age", "18" } };
			std::string data2 = "name=Marek&age=18";

			auto res1 = Marox::HTTP::POST("http://httpbin.org/post", data);
			auto res2 = Marox::HTTP::POST("http://httpbin.org/post", data2);

			Logger::WriteMessage(res1.content.c_str());
			Logger::WriteMessage(res2.content.c_str());

			Assert::AreEqual(res1.content, res2.content, L"1");
		}
	};

	TEST_CLASS(threading)
	{
	public:
		static void run(int& data, std::mutex* m)
		{
			for (size_t i = 0; i < 2000; i++)
			{
				m->lock();
				data++;
				m->unlock();
			}
		}
		static void run2(int& data, std::mutex* m)
		{
			for (size_t i = 0; i < 1000; i++)
			{
				m->lock();
				data--;
				m->unlock();
			}
		}

		TEST_METHOD(threading_1)
		{
			int counter = 0;
			std::mutex m1;

			auto t1 = Marox::Threading::CreateThreadFromFunction(run, std::ref(counter), &m1);
			auto t2 = std::thread(run2, std::ref(counter), &m1);
			t1->join();
			t2.join();

			Assert::AreEqual(counter, 1000, L"1");
		}
	};

	TEST_CLASS(FileVersionInfo_tests)
	{
	public:
		TEST_METHOD(fvi_parse_and_equal)
		{
			auto fvi1 = Marox::Tools::FileVersionInfo(1, 2, 3, 4);
			auto fvi2 = Marox::Tools::FileVersionInfo::Parse("1.2.3.4");

			Assert::IsNotNull(fvi2, L"1");

			std::string s1 = "1.2.3.4";
			std::string s2 = fvi1.ToString();
			std::string s3 = fvi2->ToString();


			Assert::AreEqual(fvi1, *fvi2, L"2");
			Assert::AreEqual(s1, s2, L"3");
			Assert::AreEqual(s2, s3, L"4");
			Assert::IsTrue((fvi1 == *fvi2), L"5");
		}

		TEST_METHOD(fvi_operators)
		{
			auto fvi1 = Marox::Tools::FileVersionInfo(1, 1, 1, 1);
			auto fvi2 = Marox::Tools::FileVersionInfo(1, 1, 1, 2);
			auto fvi3 = Marox::Tools::FileVersionInfo(1, 1, 3, 2);
			auto fvi4 = Marox::Tools::FileVersionInfo(1, 3, 4, 4);
			auto fvi5 = Marox::Tools::FileVersionInfo(1, 4, 0, 0);
			auto fvi6 = Marox::Tools::FileVersionInfo(2, 1, 1, 1);
			auto fvi7 = Marox::Tools::FileVersionInfo(2, 1, 2, 1);

			std::vector<Marox::Tools::FileVersionInfo> vec =
			{
				fvi1, fvi2, fvi3, fvi4, fvi5, fvi6, fvi7
			};

			auto max = std::max_element(vec.begin(), vec.end());
			auto min = std::min_element(vec.begin(), vec.end());

			bool isSorted = std::is_sorted(vec.begin(), vec.end());

			Logger::WriteMessage(max->ToString().c_str());
			Logger::WriteMessage(min->ToString().c_str());


			Assert::AreEqual(*max, fvi7, L"1");
			Assert::AreEqual(*min, fvi1, L"2");
			Assert::IsTrue(isSorted, L"3");
			Assert::IsTrue(((fvi2 > fvi1) && (fvi3 > fvi2) && (fvi2<fvi4) && (fvi7>fvi6)), L"4");
		}
	};
}