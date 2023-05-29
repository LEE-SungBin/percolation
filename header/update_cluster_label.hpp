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

int update_cluster_label(const int size, const int dimension, const std::vector<int> &lattice, const std::vector<std::vector<int>> &search_coordinate, std::vector<int> &label, const std::list<int> &occupied)
{
    int MAX_LABEL = 0;

    for (int i : occupied)
    {
        std::list<int> nn_list;
        for (int coord : search_coordinate[i])
        {
            if (label[coord] != 0)
            {
                nn_list.push_back(label[coord]);
            }
        }

        if (nn_list.size() == 0)
        {
            MAX_LABEL++;          // update MAX_LABEL
            label[i] = MAX_LABEL; // asign new label
        }

        else
        {
            // std::list<int>::iterator cluster = std::min_element(nn_list.begin(), nn_list.end());
            int minimum = *(std::min_element(nn_list.begin(), nn_list.end()));

            label[i] = minimum;
            for (int occupy : occupied)
            {
                if (label[occupy] != 0 && label[occupy] != minimum && std::find(nn_list.begin(), nn_list.end(), label[occupy]) != nn_list.end())
                {
                    label[occupy] = minimum; // unify label with minimum
                }
            }
        }
    }

    MAX_LABEL = 0;

    for (int i : occupied)
    {
        if (label[i] > MAX_LABEL)
        {
            int current_label = label[i];
            MAX_LABEL++;

            for (int occupy : occupied)
            {
                if (label[occupy] == current_label)
                {
                    label[occupy] = MAX_LABEL;
                }
            }
        }
    }

    return MAX_LABEL;
}