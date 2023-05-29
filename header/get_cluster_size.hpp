#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <list>
#include <numeric>

#pragma once

std::vector<int> get_size_of_cluster_by_No(const std::vector<int> &cluster_label, int total_number)
{
    std::vector<int> size_of_cluster_by_No(total_number, 0);

    for (int i = 1; i <= total_number; i++)
    {
        for (int point : cluster_label)
        {
            if (point == i) // if cluster No. is i
            {
                size_of_cluster_by_No[i - 1]++; // size_of_cluster_by_No[i]: size of cluster labeled as i + 1 since there is no cluster labeled 0
            }
        }
    }

    return size_of_cluster_by_No;
}

std::vector<int> get_num_of_cluster_by_size(const std::vector<int> &size_of_cluster_by_No, int total_number, int size, int dimension)
{
    std::vector<int> size_distribution(pow(size, dimension), 0);

    for (int i = 1; i <= pow(size, dimension); i++)
    {
        for (int j = 0; j < total_number; j++)
        {
            if (size_of_cluster_by_No[j] == i)
            {
                size_distribution[i - 1]++; // size_distribution[i]: number of cluster with size i + 1 since there is no cluster with size 0
            }
        }
    }

    return size_distribution;
}