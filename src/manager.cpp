#include "manager.h"
#include <filesystem>
#include <set>

void Manager::fillFrequencyMap(FileThreadManager &fileThreadManager, std::string file)
{
    const std::string fileName = fileThreadManager.split(file, "/").back();

    if (fileName.rfind(".", 0) == 0 || fileName.rfind("..", 0) == 0)
        return;

    if (std::filesystem::is_regular_file(fileName))
        return;

    std::string text = fileThreadManager.getTextFromFile(file);

    for (const auto &it : text)
        insertSymbol(it);
}

void Manager::insertSymbol(const char &symbol)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    ++m_frequencySymbols[symbol];
}

std::map<char, size_t> Manager::frequency() const
{
    std::lock_guard<std::mutex> guard(m_mutex);
    return m_frequencySymbols;
}

std::vector<std::pair<char, size_t>> Manager::fiveMostCommonCharacters() const
{
    std::lock_guard<std::mutex> guard(m_mutex);

    std::set<std::pair<size_t, char>> flip;

    for (auto const &kv : m_frequencySymbols)
        flip.emplace(kv.second, kv.first);

    std::vector<std::pair<char, size_t>> result;

    int i = 0;

    for (auto it = flip.rbegin(); it != flip.rend() && i < 5; ++it, ++i)
        result.push_back({ it->second, it->first });

    return result;
}

std::vector<std::pair<char, size_t> > Manager::threeMostRareCharacters() const
{
    std::lock_guard<std::mutex> guard(m_mutex);

    std::set<std::pair<size_t, char>> flip;

    for (auto const &kv : m_frequencySymbols)
        flip.emplace(kv.second, kv.first);

    std::vector<std::pair<char, size_t>> result;

    int i = 0;

    for (auto it = flip.begin(); it != flip.end() && i < 3; ++it, ++i)
        result.push_back({ it->second, it->first });

    return result;
}

double Manager::probability(const char &symbol)
{
    size_t sum = 0;

    for (const auto &it : m_frequencySymbols)
        if (it.first != symbol)
            sum += it.second;

    if (sum == 0)
        return 0;

    return m_frequencySymbols[symbol] / static_cast<double>(sum);
}
