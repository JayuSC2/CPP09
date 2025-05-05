/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:20 by juitz             #+#    #+#             */
/*   Updated: 2025/05/05 15:51:04 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <vector>
#include <vector>

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
	//std::cout << "Number of pairs: " << pairs.size() << std::endl;
    return (pairs);
}

void PmergeMe::sort_pairs(std::vector<IntPair>& pairs)
{
    std::sort(pairs.begin(), pairs.end());
}

unsigned int PmergeMe::jacobsthal(unsigned int n)
{
	unsigned int j[n + 1];

	j[0] = 0;
	j[1] = 1;

	for (unsigned int i = 2; i <= n; i++)
		j[i] = j[i - 1] + j[i - 2] * 2;
	return (j[n]);
}

std::vector<unsigned int> PmergeMe::jacobsthal_sequence(unsigned int n)
{
    std::vector<unsigned int> sequence;
    
    sequence.push_back(1);
    
    unsigned int index = 2;
    unsigned int j_index = 2;
    unsigned int j_val = jacobsthal(j_index);
    
    while (index < n)
    {
        if (j_val <= n)
            sequence.push_back(j_val);
        
        for (unsigned int k = j_val - 1; k > jacobsthal(j_index - 1) && index < n; k--)
        {
            if (k <= n)
            {
                sequence.push_back(k);
                index++;
            }
        }
        j_index++;
        j_val = jacobsthal(j_index);
        index++;
    }
    return (sequence);
}

void PmergeMe::ford_johnson_sort(std::vector<int>& arr)
{
	if (arr.size() <= 1)
		return ;
	
	std::vector<IntPair> pairs = make_pairs(arr);
	
	std::vector<int> larger_elements;
	std::vector<int> smaller_elements;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		larger_elements.push_back(pairs[i].first);
		smaller_elements.push_back(pairs[i].second);
		_operationCounter++;
	}
	ford_johnson_sort(larger_elements);

	arr.clear();
    for (size_t i = 0; i < larger_elements.size(); i++)
	{
        arr.push_back(larger_elements[i]);
	}

	if (!smaller_elements.empty())
	{
		binary_insert(arr, smaller_elements[0], 1);
		
		if (smaller_elements.size() > 1)
		{
			std::vector<unsigned int> jseq = jacobsthal_sequence(smaller_elements.size());
			
			for (size_t i = 0; i < jseq.size() && i < smaller_elements.size() -1; i++)
			{
				if (jseq[i] < smaller_elements.size())
					binary_insert(arr, smaller_elements[jseq[i]], jseq[i] + 1);
			}
		}
	}
	if (arr.size() < _vector.size() && _vector.size() % 2 != 0)
        binary_insert(arr, _unpaired, arr.size());
}

void PmergeMe::binary_insert(std::vector<int>& arr, int value, unsigned int upper_bound)
{
	unsigned int left = 0;
	unsigned int right = upper_bound;
	
	while (left < right)
	{
		unsigned int mid = left + (right - left) / 2;
		_operationCounter++;

		if (arr[mid] <= value)
			left = mid + 1;
		else
		 	right = mid;
	}
	arr.insert(arr.begin() + left, value);
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

/*     if (n == 0)
		return (0);
    if (n == 1)
		return 1;
    
    unsigned int j_prev = 0;
    unsigned int j_curr = 1;
    unsigned int j_next;
    
    for (unsigned int i = 2; i <= n; i++)
    {
        j_next = j_curr + 2 * j_prev;
        j_prev = j_curr;
        j_curr = j_next;
    }
    return (j_curr);
}
	*/
