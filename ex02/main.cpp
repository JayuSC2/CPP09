/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:54:41 by juitz             #+#    #+#             */
/*   Updated: 2025/06/26 14:52:19 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
    {
        std::cerr << "Error: No arguments provided" << std::endl;
        std::cerr << "Usage: ./PmergeMe [positive integers...]" << std::endl;
        return (1);
    }
	if (argc > 3001)
		return (std::cerr << "Error: too many arguments" << std::endl, 1);
	PmergeMe sort;
	if (sort.parse_vector(argc, argv) != 0)
		return (1);
	std::cout << "Vector Before: ";
	for (int i = 0; i < argc - 1; i++)
	{
		std::cout << sort.get_vector()[i] << " ";
	}
	std::cout << std::endl;
	if (sort.parse_deque(argc, argv) != 0)
		return (1);
	std::cout << "Deque Before: ";
	for (int i = 0; i < argc - 1; i++)
	{
		std::cout << sort.get_deque()[i] << " ";
	}
	std::cout << std::endl;
	clock_t start = clock();
	// std::vector<unsigned int> jseq = sort.jacobsthal_sequence_vec(sort.get_vector().size());
	// std::cout << "Jacobsthal sequence: ";
	// for (size_t i = 0; i < jseq.size() - 1; i++)
	// 	std::cout << jseq[i] << " ";
	// std::cout << std::endl;
	sort.sorter_vec();
	std::cout << "Vector After: ";
	for (int i = 0; i < argc - 1; i++)
	{
		std::cout << sort.get_vector()[i] << " ";
	}
	std::cout << std::endl;
	clock_t end = clock();
/* 	clock_t start2 = clock();
	sort.sorter_dq();
	std::cout << "Deque After: ";
	for (int i = 0; i < argc - 1; i++)
	{
		std::cout << sort.get_deque()[i] << " ";
	}
	clock_t end2 = clock();
	std::cout << std::endl; */
	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;
	//double elapsed2 = double(end2 - start2) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << sort.get_vector().size() << " elements with std::vector " << elapsed << " ms" << std::endl;
	//std::cout << "Time to process a range of " << sort.get_deque().size() << " elements with std::deque " << elapsed2 << " ms" << std::endl;
	std::cout << "Number of comparisons: " << sort.get_operations() << std::endl;
	//sort.sorter();
	/* for (size_t i = 0; i < sort.get_vector().size(); i++)
		std::cout << sort.get_vector()[i] << std::endl; 
	for (size_t i = 0; i < pairs.size(); i++)
	{
		std::cout << pairs[i] << std::endl;
	} */
	// if (sort.is_sorted())
	// 	std::cout << "Array is sorted" << std::endl;
	return (0);
}
