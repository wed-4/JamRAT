#include "FileCommand.h"
#include <fstream>

std::string FileCommand::GetCrentDirectory()
{
    std::filesystem::path path = std::filesystem::current_path();

    std::string currentPathString = path.string();
    return currentPathString;
}


