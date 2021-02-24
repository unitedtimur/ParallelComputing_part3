#include<iostream>
#include <algorithm>
#include "filethreadmanager.h"
#include "manager.h"
#include <map>
#include <sstream>
#include <filesystem>
#include <thread>
#include <set>

int main()
{
    FileThreadManager fileThreadManager;
    const auto files = fileThreadManager.getFileNames("/home/unitedtimur/education/projects_c++/SecondLab");

    Manager manager;

    std::vector<std::thread> threads;

    for (const auto &file : files)
        threads.push_back(std::thread([&]() {
            manager.fillFrequencyMap(fileThreadManager, file);
        }));

    for (size_t i = 0; i < threads.size(); ++i)
        if (threads.at(i).joinable())
            threads.at(i).join();

    std::thread mainThread([&]() {
        std::string command;

        for (;;) {
            std::cout << "Enter the command: " << std::flush;
            std::cin >> command;

            if (command.rfind("mo", 0) == 0) {
                for (const auto &it : manager.fiveMostCommonCharacters()) {
                    std::cout << "\t" << it.first << " " << it.second << std::endl;
                }
            } else if (command.rfind("mr", 0) == 0) {
                for (const auto &it : manager.threeMostRareCharacters()) {
                    std::cout << "\t" << it.first << " " << it.second << std::endl;
                }
            } else if (command.rfind("pr", 0) == 0) {
                char symbol;

                std::cout << "Enter the symbol: " << std::flush;
                std::cin >> symbol;
                std::cout << "\t" << manager.probability(symbol) << std::endl;
            } else if (command.rfind("hl", 0) == 0) {
                std::cout << "\tmo - five most commot characters" << std::endl
                          << "\tmr - three most rare characters" << std::endl
                          << "\tpr - probability of symbol" << std::endl;
            }
            else {
                std::cout << "Some shit happens ;(" << std::endl;
            }
        }
    });

    if (mainThread.joinable())
        mainThread.join();

    return 0;
}
