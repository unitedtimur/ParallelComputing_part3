#include "filethreadmanager.h"
#include <filesystem>
#include <fstream>
#include <regex>

ttd::stringlist FileThreadManager::getFileNames(const std::string &path) const
{
    std::lock_guard<std::mutex> guard(m_mutex);

    ttd::stringlist stringlist;

    for (const auto & entry : std::filesystem::directory_iterator(path))
        stringlist.emplace_back(entry.path().string());

    return stringlist;
}

std::string FileThreadManager::getTextFromFile(const std::string &fileName) const
{
    try {
        std::lock_guard<std::mutex> guard(m_mutex);

        std::ifstream in(fileName);

        std::string data;

        data.assign((std::istreambuf_iterator<char>(in.rdbuf())), std::istreambuf_iterator<char>());

        return data;
    }  catch (...) {
        return std::string();
    }
}

std::vector<std::string> FileThreadManager::split(const std::string &input, const std::string &regex)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    std::regex re(regex);
    std::sregex_token_iterator first{ input.begin(), input.end(), re, -1 }, last;
    return { first, last };
}
