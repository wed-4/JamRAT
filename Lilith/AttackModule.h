#pragma once
#include <iostream>
#include <vector>
#include <windows.h>

class AttackModule
{
public:
	void ModuleLoad(int id);
	std::vector<std::wstring> ModuleList();
	
};

