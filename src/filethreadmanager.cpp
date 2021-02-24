#include "filethreadmanager.h"
#include <filesystem>
#include <fstream>

ttd::stringlist FileThreadManager::getFileNames(const std::string &&path) const
{
    ttd::stringlist stringlist;

    for (const auto & entry : std::filesystem::directory_iterator(path))
        stringlist.emplace_back(entry.path().string());

    return stringlist;
}

std::string FileThreadManager::getTextFromFile(const std::string &&fileName) const
{
    std::ifstream in(fileName);

    std::string data;

    data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());

    return data;
}
