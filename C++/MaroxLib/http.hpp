#pragma once
#include "detail\http\Common\Include\WinHttpClient.h"
#include "convert.hpp"
#include <map>
#include <sstream>


namespace Marox
{
	namespace HTTP
	{
		struct Response
		{
			Response(std::string _header, std::string _content)
			{
				this->header = _header;
				this->content = _content;
			}
			std::string header;
			std::string content;
		};
		Response GET(const std::string& _url, bool(*_callback)(double) = nullptr)
		{
			WinHttpClient* client;
			if (_callback)
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url), _callback);
			}
			else
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url));
			}
			client->SetTimeouts(0U, 20000U, 30000U, 20000U);
			client->SendHttpRequest();
			Response res(Tools::Convert::wstring_to_string(client->GetResponseHeader()), Tools::Convert::wstring_to_string(client->GetResponseContent()));
			delete client;
			return res;
		}
		Response GET(const std::string& _url, const std::string& _filePath, bool(*_callback)(double) = nullptr)
		{
			WinHttpClient* client;
			if (_callback)
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url), _callback);
			}
			else
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url));
			}
			client->SendHttpRequest();
			Response res(Tools::Convert::wstring_to_string(client->GetResponseHeader()), "Content written to: " + _filePath);
			client->SaveResponseToFile(Tools::Convert::string_to_wstring(_filePath));
			delete client;
			return res;
		}
		Response POST(const std::string& _url, const std::string& _data, bool(*_callback)(double) = nullptr)
		{
			WinHttpClient* client;
			if (_callback)
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url), _callback);
			}
			else
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url));
			}

			client->SetAdditionalDataToSend((BYTE *)_data.c_str(), _data.size());

			// Set request headers.
			wchar_t szSize[50] = L"";
			swprintf_s(szSize, L"%d", _data.size());
			wstring headers = L"Content-Length: ";
			headers += szSize;
			headers += L"\r\nContent-Type: application/x-www-form-urlencoded\r\n";
			client->SetAdditionalRequestHeaders(headers);

			// Send HTTP post request.
			client->SendHttpRequest(L"POST");

			Response res(Tools::Convert::wstring_to_string(client->GetResponseHeader()), Tools::Convert::wstring_to_string(client->GetResponseContent()));
			delete client;
			return res;
		}
		Response POST(const std::string& _url, const std::map<std::string, std::string>& _data, bool(*_callback)(double) = nullptr)
		{
			std::stringstream ss;
			for (auto& it : _data)
			{
				ss << it.first;
				ss << "=";
				ss << it.second;
				ss << "&";
			}

			string data = ss.str();
			data.pop_back();

			WinHttpClient* client;
			if (_callback)
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url), _callback);
			}
			else
			{
				client = new WinHttpClient(Tools::Convert::string_to_wstring(_url));
			}
			client->SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());

			// Set request headers.
			wchar_t szSize[50] = L"";
			swprintf_s(szSize, L"%d", data.size());
			wstring headers = L"Content-Length: ";
			headers += szSize;
			headers += L"\r\nContent-Type: application/x-www-form-urlencoded\r\n";
			client->SetAdditionalRequestHeaders(headers);

			// Send HTTP post request.
			client->SendHttpRequest(L"POST");

			Response res(Tools::Convert::wstring_to_string(client->GetResponseHeader()), Tools::Convert::wstring_to_string(client->GetResponseContent()));
			delete client;
			return res;
		}
	}
}