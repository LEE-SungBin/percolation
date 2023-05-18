#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "./header/sum.h"

// using namespace std;

int main()
{
    std::vector<std::string> msg{"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (std::string &word : msg)
    {
        std::cout << word << " ";
    }

    std::cout << sum(2, 4);

    std::cout << std::endl;
}