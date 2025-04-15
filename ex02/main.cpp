/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:54:41 by juitz             #+#    #+#             */
/*   Updated: 2025/04/15 17:22:13 by juitz            ###   ########.fr       */
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
	if (argc > 3000)
		return (std::cerr << "Error: too many arguments" << std::endl, 1);
	PmergeMe sort;
	//std::vector<int> numbers;
	if (sort.parse_input(argc, argv) == 0)
	{
		for (int i = 0; i < argc - 1; i++)
		{
			std::cout << sort.getVector()[i] << std::endl;
		}
	}
	sort.make_pairs();
	return (0);
}

/* #include <bits/stdc++.h>

int Jacobsthal(int n)
{
	int j[n + 1];

	j[0] = 0;
	j[1] = 1;

	for (int i = 2; i <= n; i++)
		j[i] = j[i - 1] + j[i - 2] * 2;
	return (j[n]);
}

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