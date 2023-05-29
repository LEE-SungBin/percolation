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

std::vector<std::vector<int>> get_coordinate(const int size, const int dimension)
{
    std::vector<std::vector<int>> coordinate(pow(size, dimension), std::vector<int>(dimension, 0));

    for (int i = 0; i < coordinate.size(); i++)
    {
        for (int j = 0; j < coordinate[i].size(); j++)
        {
            coordinate[i][j] = int(i / pow(size, j)) % size;
        }
    }

    return coordinate;
}

std::vector<std::vector<int>> get_nn_coordinate(const int size, const int dimension)
{
    std::vector<std::vector<int>> nn_coordinate(pow(size, dimension), std::vector<int>(2 * dimension, 0));
    std::vector<std::vector<int>> coordinate = get_coordinate(size, dimension);

    for (int i = 0; i < nn_coordinate.size(); i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            nn_coordinate[i][2 * j] = i + ((coordinate[i][j] + 1) % size - coordinate[i][j]) * pow(size, j);
            nn_coordinate[i][2 * j + 1] = i + ((coordinate[i][j] - 1 + size) % size - coordinate[i][j]) * pow(size, j);
        }
    }

    return nn_coordinate;
}

std::vector<std::vector<int>> get_search_coordinate(const int size, const int dimension)
{
    const std::vector<std::vector<int>> coordinate = get_coordinate(size, dimension);
    typedef std::vector<std::vector<int>> Search_coordinate;
    typedef std::vector<int> Row;

    Search_coordinate search_coordinate;

    const size_t N = pow(size, dimension);

    for (size_t i = 0; i < N; i++)
    {
        Row row;

        for (int j = 0; j < dimension; j++)
        {
            if (coordinate[i][j] != 0)
            {
                row.push_back(i - pow(size, j));
            }
        }

        search_coordinate.push_back(row);
    }

    return search_coordinate;
}

std::vector<std::vector<int>> get_boundary_coordinate(const int size, const int dimension)
{
    const std::vector<std::vector<int>> coordinate = get_coordinate(size, dimension);
    typedef std::vector<std::vector<int>> Boundary;
    // boundary_coordinate(2 * dimension, std::vector<int>(pow(size, dimension - 1), 0));

    Boundary boundary_coordinate;

    for (int j = 0; j < dimension; j++)
    {
        std::vector<int> row1, row2;

        for (int i = 0; i < pow(size, dimension); i++)
        {
            if (coordinate[i][j] == 0)
            {
                row1.push_back(i);
            }

            else if (coordinate[i][j] == size - 1)
            {
                row2.push_back(i);
            }
        }

        boundary_coordinate.push_back(row1); // coordinate of "bottom"
        boundary_coordinate.push_back(row2); // coordinate of "ceiling"
    }

    return boundary_coordinate;
}