#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <mutex>
#include <utility>
#include "filethreadmanager.h"

class Manager final
{
public:
    explicit Manager() = default;

    void fillFrequencyMap(FileThreadManager &fileThreadManager, std::string file);

    void insertSymbol(const char &symbol);
    std::map<char, size_t> frequency() const;

    std::vector<std::pair<char, size_t>> fiveMostCommonCharacters() const;
    std::vector<std::pair<char, size_t>> threeMostRareCharacters() const;
    double probability(const char &symbol);

private:
    std::map<char, size_t> m_frequencySymbols;
    mutable std::mutex m_mutex;
};

#endif // MANAGER_H
