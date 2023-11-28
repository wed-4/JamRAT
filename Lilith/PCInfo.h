#pragma once
#include <string>
class PCInfo
{
	std::string GetLAN();
	std::string GetWAN();
	std::string GetUserName();
	std::string GetPCName();
	std::string GetOSName();
	int GetCore();
};

