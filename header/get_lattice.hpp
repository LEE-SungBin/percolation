#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <list>

#pragma once

std::vector<int> get_lattice(int size, int dimension, double probability)
{
    std::srand(time(NULL));

    std::vector<int> lattice(pow(size, dimension), 0);

    for (int i = 0; i < pow(size, dimension); i++)
    {
        if ((double)std::rand() / (RAND_MAX) <= probability)
        {
            lattice[i] = 1;
        }
    }

    return lattice;
}