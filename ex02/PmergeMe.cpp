/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:20 by juitz             #+#    #+#             */
/*   Updated: 2025/04/18 15:43:41 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>


PmergeMe::PmergeMe() : _vector(0), _unpaired(0), _operationCounter(0)
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
	this->_vector = copy._vector;
	this->_unpaired = copy._unpaired;
	this->_operationCounter = copy._operationCounter;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_unpaired = other._unpaired;
		this->_operationCounter = other._operationCounter;
	}
	return (*this);
}

const std::vector<int>& PmergeMe::get_vector() const
{
    return (_vector);
}

const unsigned int& PmergeMe::get_operations() const
{
	return (_operationCounter);
}

int	PmergeMe::parse_input(int argc, char **argv)
{
	_vector.clear();
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		int num;

		if (!(iss >> num) || num < 0 || iss.peek() != EOF)
		{
			std::cerr << "Error: Invalid argument '" << argv[i] << "'. Only positive integers are allowed. " << std::endl;
			return (1);
		}
		_vector.push_back(num);
	}
	return (0);
}

std::vector<PmergeMe::IntPair> PmergeMe::make_pairs(const std::vector<int>& input)
{
    std::vector<IntPair> pairs;
    
    for (size_t i = 0; i < input.size() - 1; i += 2)
    {
        if (input[i] > input[i + 1])
		{
            pairs.push_back(std::make_pair(input[i], input[i + 1]));
			_operationCounter += 1;
		}
        else
		{
            pairs.push_back(std::make_pair(input[i + 1], input[i]));
			_operationCounter += 1;
		}
    }
	if (_vector.size() % 2 != 0)
		_unpaired = _vector[_vector.size() - 1];
	std::cout << "Number of pairs: " << pairs.size() << std::endl;
    return (pairs);
}

void PmergeMe::sort_pairs(std::vector<IntPair>& pairs)
{
    std::sort(pairs.begin(), pairs.end());
}

void PmergeMe::ford_johnson_sort(std::vector<int>& arr)
{
	if (arr.size() <= 1)
		return ;
	
	std::vector<IntPair> pairs = make_pairs(arr);
	
	std::vector<int> larger_elements;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		larger_elements.push_back(pairs[i].first);
		_operationCounter++;
	}
	ford_johnson_sort(larger_elements);

	
}

void PmergeMe::sorter()
{
    std::vector<int> working_copy = _vector;
     _operationCounter = 0;
    ford_johnson_sort(working_copy);
    _vector = working_copy;
}
std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& pair)
{
	os << "(" << pair.first << ", " << pair.second << ")";
	return (os);
}

