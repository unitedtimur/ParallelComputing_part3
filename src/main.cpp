#include<iostream>
#include <algorithm>
#include "filethreadmanager.h"
#include <map>
#include <sstream>

int main()
{
    FileThreadManager fileThreadManager;
    //    const auto fa = fileThreadManager.getFileNames("/home/unitedtimur/education/projects_c++/SecondLab");

    //    std::for_each(fa.begin(), fa.end(), [](auto value){
    //        std::cout << value << std::endl;
    //    });


    std::string text = fileThreadManager.getTextFromFile("/home/unitedtimur/education/projects_c++/SecondLab/CMakeLists.txt");

    std::map<char, size_t> result;
    std::stringstream inputStringStream(text);

    for (const auto &it : text) {
        result[it]++;
    }

    for (auto it = result.begin(); it != result.end(); ++it)
        std::cout << it->first << " " << it->second << std::endl;

    return 0;
}
