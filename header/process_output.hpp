#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <list>
#include <numeric>
#include "./get_coordinate.hpp"

#pragma once

std::vector<int> infinite_cluster_test(const std::vector<int> &cluster_label, const std::vector<std::vector<int>> &boundary_coordinate, const int total_number, const int size, const int dimension)
{
    std::vector<int> oracle(total_number, 0);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < pow(size, dimension - 1); j++)
        {
            int coord1 = boundary_coordinate[2 * i][j];
            int coord2 = boundary_coordinate[2 * i + 1][j];

            // std::cout << coord1 << "\n";
            if (cluster_label[coord1] != 0 && cluster_label[coord2] != 0 && cluster_label[coord1] == cluster_label[coord2])
            {
                oracle[cluster_label[coord1] - 1] = 1; // position of cluster No. i is i - 1
                break;
            }
        }
    }

    return oracle;
}

double get_order_parameter(const std::vector<int> &size_of_inf_c_by_No)
{
    return std::accumulate(size_of_inf_c_by_No.begin(), size_of_inf_c_by_No.end(), 0.0);
}

double get_susceptibility(const std::vector<int> &size_of_noninf_c_by_No)
{
    return std::inner_product(size_of_noninf_c_by_No.begin(), size_of_noninf_c_by_No.end(), size_of_noninf_c_by_No.begin(), 0.0);
}

double get_total_number(const std::vector<int> &size_of_noninf_c_by_No)
{
    return size_of_noninf_c_by_No.size();
}

double get_avg_size(const std::vector<int> &size_of_noninf_c_by_No)
{
    if (size_of_noninf_c_by_No.size() == 0)
    {
        return 0.0;
    }
    else
    {
        double numerator = 0.0;
        double denominator = 0.0;

        for (int i : size_of_noninf_c_by_No)
        {
            numerator += pow(i, 2);
            denominator += i;
        }

        return numerator / denominator;
    }
}

double get_std_size(const std::vector<int> &size_of_noninf_c_by_No)
{
    if (size_of_noninf_c_by_No.size() == 0)
    {
        return 0.0;
    }
    else
    {
        double numerator = 0.0;
        double denominator = 0.0;

        for (int i : size_of_noninf_c_by_No)
        {
            numerator += pow(i, 3);
            denominator += i;
        }

        const double avg = get_avg_size(size_of_noninf_c_by_No);

        return std::sqrt(numerator / denominator - avg * avg);
    }
}