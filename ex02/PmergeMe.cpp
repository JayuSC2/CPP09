/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:20 by juitz             #+#    #+#             */
/*   Updated: 2025/04/14 17:22:03 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <istream>
#include <vector>

PmergeMe::PmergeMe() : _vector(0)
{
}

PmergeMe::PmergeMe(std::vector<int> vector) : _vector(vector)
{
}

PmergeMe::~PmergeMe()
{
	std::cout << "PmergeMe default destructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	this->_maxCount = copy._maxCount;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
		this->_maxCount = other._maxCount;
	return (*this);
}

std::vector<int> parse_input(int argc, char **argv);
{
	
}
