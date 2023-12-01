#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <winInet.h>
#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "wininet.lib")

class PCInfo
{
public:
	std::string GetLAN();
	std::string GetWAN();
	std::string GetuserName();
	std::string GetPCName();
	int GetCore();
};

