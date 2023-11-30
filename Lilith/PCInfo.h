#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <afxinet.h>
#pragma comment(lib, "winhttp.lib")

class PCInfo
{
	std::string GetLAN();
	std::string GetWAN();
	std::string GetuserName();
	std::string GetPCName();
	int GetCore();
};

