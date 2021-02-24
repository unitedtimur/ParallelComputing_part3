#ifndef FILETHREADMANAGER_H
#define FILETHREADMANAGER_H

#include <vector>
#include <string>
#include <mutex>

namespace ttd {
using stringlist = std::vector<std::string>;
}

class FileThreadManager
{

public:
    explicit FileThreadManager() = default;

    ttd::stringlist getFileNames(const std::string &path) const;

    std::string getTextFromFile(const std::string &fileName) const;

    std::vector<std::string> split(const std::string &input, const std::string &regex);

private:
    mutable std::mutex m_mutex;
};

#endif // FILETHREADMANAGER_H
