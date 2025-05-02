/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:54:41 by juitz             #+#    #+#             */
/*   Updated: 2025/05/02 16:46:24 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>

// int main(int argc, char **argv)
// {
// 	(void) argv;
// 	(void) argc;
// 	if (argc != 2)
// 		return (std::cout << "incorrect arguments" << std::endl, 1);
// 	PmergeMe test;
// 	/* unsigned int jt = test.jacobsthal(atoi(argv[1]));
// 	std::cout << "Jacobsthal num: " << jt << std::endl; */
// 	std::vector<unsigned int> jts;
// 	unsigned int len = 20;
// 	jts = test.jacobsthal_sequence(len);
// 	for (unsigned int i = 0; i < len; i++)
// 		std::cout << jts[i] << std::endl;
// 	return (0);
// }

int main(int argc, char **argv)
{
	if (argc < 2)
    {
        std::cerr << "Error: No arguments provided" << std::endl;
        std::cerr << "Usage: ./PmergeMe [positive integers...]" << std::endl;
        return (1);
    }
	if (argc > 3000)
		return (std::cerr << "Error: too many arguments" << std::endl, 1);
	PmergeMe sort;
	//std::vector<int> numbers;
	if (sort.parse_input(argc, argv) != 0)
		return (1);
	std::cout << "Before: ";
	for (int i = 0; i < argc - 1; i++)
	{
		std::cout << sort.get_vector()[i] << " ";
	}
	std::cout << std::endl;
	clock_t start = clock();
	std::vector<PmergeMe::IntPair> pairs;
	pairs = sort.make_pairs(sort.get_vector());
	sort.sort_pairs(pairs);;
	sort.sorter();
	std::cout << "After: ";
	for (int i = 0; i < argc - 1; i++)
	{
		std::cout << sort.get_vector()[i] << " ";
	}
	clock_t end = clock();
	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << sort.get_vector().size() << " elements with std::vector " << elapsed << " ms" << std::endl;
	//std::cout << "Number of comparisons: " << sort.get_operations() << std::endl;
	//sort.sorter();
	/* for (size_t i = 0; i < sort.get_vector().size(); i++)
		std::cout << sort.get_vector()[i] << std::endl; 
	for (size_t i = 0; i < pairs.size(); i++)
	{
		std::cout << pairs[i] << std::endl;
	} */

	return (0);
}

/* #include <bits/stdc++.h>

void isPresent(std::vector<int> &arr, int val)
{
    if (binary_search(arr.begin(), arr.end(), val))
        std::cout << val << " exists in vector";
    else
        std::cout << val << " does not exist";

    std::cout << std::endl;
}

int main(void)

int main(void)
{
	std::cout << Jacobsthal(12) << std::endl;
    std::vector<int> arr;
	arr.resize(7);
	
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 15;
	arr[5] = 17;
	arr[6] = 23;
	//arr[7] = 25;

    int val1 = 11;
    int val2 = 23;

    isPresent(arr, val1);
    isPresent(arr, val2);

    return (0);
} */