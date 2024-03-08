#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <filesystem>
class FileCommand
{
public:
	std::string GetCrentDirectory();
	std::string FileDownload(std::string path);
};

