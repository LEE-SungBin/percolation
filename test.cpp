#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <list>
#include <numeric>
#include <chrono>
#include "./header/get_coordinate.hpp"
#include "./header/update_cluster_label.hpp"
#include "./header/get_cluster_size.hpp"
#include "./header/process_output.hpp"

int main(int argc, char *argv[])
{
    const int size = std::stoi(argv[1]);
    const int dimension = std::stoi(argv[2]);
    const double probability = std::stod(argv[3]);
    const int ensemble = std::stoi(argv[4]);

    std::srand(time(0));

    auto begin = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> search_coordinate = get_search_coordinate(size, dimension);     // get search coordinate of lattice
    const std::vector<std::vector<int>> boundary_coordinate = get_boundary_coordinate(size, dimension); // get boundary coordinate of lattice

    for (int i = 0; i < ensemble; i++)
    {
        std::vector<int> lattice(pow(size, dimension), 0);       // 0 for un-occupied state, 1 for occupied state
        std::vector<int> cluster_label(pow(size, dimension), 0); // 0 for un-occupied state, 1 ~ total_number for occupied cluster
        std::list<int> occupied;                                 // list of occupied state No.

        for (int i = 0; i < pow(size, dimension); i++)
        {
            if ((double)std::rand() / (RAND_MAX) <= probability)
            {
                lattice[i] = 1;
                occupied.push_back(i);
            }
            std::cout << lattice[i] << " ";

            if (i % size == size - 1)
            {
                std::cout << "\n";
            }
        }

        std::cout << "\n";

        int total_number = update_cluster_label(size, dimension, lattice, search_coordinate, cluster_label, occupied); // update cluster label and return total number of cluster

        for (int i = 0; i < pow(size, dimension); i++)
        {
            std::cout << cluster_label[i] << " ";
            if (i % size == size - 1)
            {
                std::cout << "\n";
            }
        }

        const std::vector<int> size_of_cluster_by_No = get_size_of_cluster_by_No(cluster_label, total_number);

        // double max = *(std::max_element(size_of_cluster_by_No.begin(), size_of_cluster_by_No.end()));
        std::vector<int> num_of_cluster_by_size = get_num_of_cluster_by_size(size_of_cluster_by_No, total_number, size, dimension);
        std::cout << "\nnumber of cluster by size: ";
        for (int i : num_of_cluster_by_size)
        {
            std::cout << i << " ";
        }

        std::vector<int> infinite_cluster = infinite_cluster_test(cluster_label, boundary_coordinate, total_number, size, dimension);
        std::vector<int> size_of_noninf_c_by_No;
        std::vector<int> size_of_inf_c_by_No;

        for (int i = 0; i < size_of_cluster_by_No.size(); i++)
        {
            if (infinite_cluster[i] == 0)
            {
                size_of_noninf_c_by_No.push_back(size_of_cluster_by_No[i]);
            }
            else if (infinite_cluster[i] == 1)
            {
                size_of_inf_c_by_No.push_back(size_of_cluster_by_No[i]);
            }
        }

        double order_parameter = get_order_parameter(size_of_inf_c_by_No) / pow(size, dimension);
        double susceptibility = get_susceptibility(size_of_noninf_c_by_No) / pow(size, dimension);
        double num = get_total_number(size_of_noninf_c_by_No);
        double avg = get_avg_size(size_of_noninf_c_by_No);
        double std = get_std_size(size_of_noninf_c_by_No);

        std::cout << "\n\nsize: " << size << " | dimension: " << dimension << " | probability: " << probability << " | ensemble: " << ensemble;
        std::cout << "\nnumber of non-inf cluster: " << num;
        std::cout << "\nsize of non-inf cluster: avg " << avg << " | std " << std;
        std::cout << "\norder parameter: " << order_parameter << " | susceptibility: " << susceptibility << "\n\n===================================\n";
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "\ntime: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / pow(10, 9) << "s";

    // delete[] &lattice;

    return 0;
}