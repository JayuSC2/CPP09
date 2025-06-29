/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:20 by juitz             #+#    #+#             */
/*   Updated: 2025/06/29 07:34:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vector(0), _deque(0), _unpaired(0), _comparisonCounter(0)
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
	this->_deque = copy._deque;
	this->_unpaired = copy._unpaired;
	this->_comparisonCounter = copy._comparisonCounter;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
		this->_unpaired = other._unpaired;
		this->_comparisonCounter = other._comparisonCounter;
	}
	return (*this);
}

const std::vector<int>& PmergeMe::get_vector() const
{
    return (_vector);
}

const std::deque<int>& PmergeMe::get_deque() const
{
	return (_deque);
}

const unsigned int& PmergeMe::get_operations() const
{
	return (_comparisonCounter);
}

int	PmergeMe::parse_vector(int argc, char **argv)
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

int	PmergeMe::parse_deque(int argc, char **argv)
{
	_deque.clear();
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream iss(argv[i]);
		int num;

		if (!(iss >> num) || num < 0 || iss.peek() != EOF)
		{
			std::cerr << "Error: Invalid argument '" << argv[i] << "'. Only positive integers are allowed. " << std::endl;
			return (1);
		}
		_deque.push_back(num);
	}
	return (0);
}

std::vector<PmergeMe::IntPair> PmergeMe::make_pairs(const std::vector<int>& input, int& unpaired)
{
    std::vector<IntPair> pairs;

    for (size_t i = 0; i < input.size() - 1; i += 2)
    {
        IntPair pair;
        if (input[i] > input[i + 1])
        {
            pair.first = input[i];
            pair.second = input[i + 1];
        }
        else
        {
            pair.first = input[i + 1];
            pair.second = input[i];
        }
        pair.original_index = i/2;
        pairs.push_back(pair);
        _comparisonCounter++;
    }
    if (input.size() % 2 != 0)
    {
        unpaired = input[input.size() - 1];
    }
    else
    {
        unpaired = -1;
    }
    return (pairs);
}

std::deque<PmergeMe::IntPair> PmergeMe::make_pairs(const std::deque<int>& input, int& unpaired)
{
    std::deque<IntPair> pairs;

    for (size_t i = 0; i < input.size() - 1; i += 2)
    {
        IntPair pair;
        if (input[i] > input[i + 1])
        {
            pair.first = input[i];
            pair.second = input[i + 1];
        }
        else
        {
            pair.first = input[i + 1];
            pair.second = input[i];
        }
        pair.original_index = i/2;
        pairs.push_back(pair);
        _comparisonCounter++;
    }
    if (input.size() % 2 != 0)
    {
        unpaired = input[input.size() - 1];
    }
    else
    {
        unpaired = -1;
    }
    return (pairs);
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

std::vector<unsigned int> PmergeMe::jacobsthal_sequence_vec(unsigned int n)
{
    std::vector<unsigned int> sequence;

    // Return an empty sequence if there are no elements to process.
    if (n == 0)
    {
        return (sequence);
    }
    // The sequence always starts with the second element (index 1).
    sequence.push_back(1);

    // Initialize with the third Jacobsthal number (J_3 = 3).
    unsigned int j_index = 3;
    unsigned int j_val = jacobsthal(j_index);

    // Continue generating the sequence until all necessary indices are included.
    while (sequence.size() < n - 1)
    {
        // Add the Jacobsthal number itself as the next insertion index.
        if (j_val < n)
            sequence.push_back(j_val);

        // Get the previous Jacobsthal number to define the current block.
        unsigned int prev_j_val = jacobsthal(j_index - 1);
        // Iterate backwards from the current Jacobsthal number down to the previous one.
        for (unsigned int k = j_val - 1; k > prev_j_val && sequence.size() < n; k--)
        {
            // Add these indices in descending order to the sequence.
            sequence.push_back(k);
        }
        // Move to the next Jacobsthal number for the next block.
        j_index++;
        j_val = jacobsthal(j_index);
    }
    return (sequence);
}

void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
{
	// Base case for the recursion: a list of 0 or 1 is already sorted.
    if (arr.size() <= 1)
	{
        return ;
	}
	
	// Create pairs from the input array and identify any leftover element.
    int level_unpaired = -1;
    std::vector<IntPair> pairs = make_pairs(arr, level_unpaired);

	// Separate the pairs into two lists: one of larger and one of smaller elements.
    std::vector<int> larger_elements;
    std::vector<int> smaller_elements;
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        larger_elements.push_back(pairs[i].first);
        smaller_elements.push_back(pairs[i].second);
    }

	// Recursively sort the list of larger elements.
    int recursive_unpaired = -1;
    ford_johnson_sort(larger_elements, recursive_unpaired);
    
	// Rebuild the main array `arr` to be the sorted main chain.
    arr.clear();
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        arr.push_back(larger_elements[i]);
    }

	// Begin inserting the smaller elements into the sorted main chain.
    if (!smaller_elements.empty())
    {
		// Find the smaller element (b_1) that was paired with the smallest larger element (a_1).
        int first_larger = larger_elements[0];
        int first_smaller = -1;
        size_t first_pair_idx = (size_t) -1;
        
        for (size_t i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].first == first_larger)
            {
                first_smaller = pairs[i].second;
                first_pair_idx = i;
                break ;
            }
        }
        // Insert b_1 at the beginning of the main chain; no search is needed.
        if (first_smaller != -1)
        {
            arr.insert(arr.begin(), first_smaller);
        }
        
		// Insert the rest of the smaller elements.
        if (smaller_elements.size() > 1)
		{
			// Generate the optimized insertion order using the Jacobsthal sequence.
			std::vector<unsigned int> jseq = jacobsthal_sequence_vec(larger_elements.size());
			// Keep track of which elements have been inserted.
			std::vector<bool> inserted(pairs.size(), false);
		
			if (first_pair_idx != (size_t) -1)
				inserted[first_pair_idx] = true;
		
			// Use Jacobsthal sequence on the SORTED larger elements
			for (size_t i = 0; i < jseq.size(); i++)
			{
				unsigned int larger_idx = jseq[i];
				
				// Mark b_1 as already inserted.
				if (larger_idx < larger_elements.size())
				{
					int target_larger = larger_elements[larger_idx];
					
					// Find the corresponding smaller element in the original pairs
					int corresponding_smaller = -1;
					size_t pair_idx = (size_t) -1;
					
					for (size_t j = 0; j < pairs.size(); j++)
					{
						if (pairs[j].first == target_larger && !inserted[j])
						{
							corresponding_smaller = pairs[j].second;
							pair_idx = j;
							break ;
						}
					}
					
					if (corresponding_smaller != -1)
					{
						// Find position of the larger element in current array
						size_t upper_bound_pos = 0;
						for (; upper_bound_pos < arr.size(); upper_bound_pos++)
						{
							if (arr[upper_bound_pos] == target_larger)
								break ;
						}
						
						// Binary insert with the larger element as upper bound
						binary_insert(arr, corresponding_smaller, upper_bound_pos);
						inserted[pair_idx] = true;
					}
				}
			}
			
			// Handle any remaining uninserted pairs
			for (size_t i = 0; i < pairs.size(); i++)
			{
				if (!inserted[i])
				{
					int current_larger = pairs[i].first;
					int current_smaller = pairs[i].second;
					
					size_t upper_bound_pos = 0;
					for (; upper_bound_pos < arr.size(); upper_bound_pos++)
					{
						if (arr[upper_bound_pos] == current_larger)
							break ;
					}
					
					binary_insert(arr, current_smaller, upper_bound_pos);
				}
			}
		}
	}
	if (level_unpaired != -1)
    {
        binary_insert(arr, level_unpaired, arr.size());
    }
    unpaired = level_unpaired;
}

size_t PmergeMe::binary_insert(std::vector<int>& arr, int value, size_t upper_bound)
{
    unsigned int left = 0;
    unsigned int right = upper_bound;
    
    while (left < right)
    {
        unsigned int mid = left + (right - left) / 2;
        _comparisonCounter++;
        if (arr[mid] <= value)
            left = mid + 1;
        else
            right = mid;
    }
    arr.insert(arr.begin() + left, value);
    return (left);
}

std::deque<unsigned int> PmergeMe::jacobsthal_sequence_dq(unsigned int n)
{
    std::deque<unsigned int> sequence;

    if (n == 0)
	{
        return (sequence);
	}
	sequence.push_back(1);

    unsigned int j_index = 3;
    unsigned int j_val = jacobsthal(j_index);

    while (sequence.size() < n - 1)
    {
        if (j_val < n)
            sequence.push_back(j_val);

        unsigned int prev_j_val = jacobsthal(j_index - 1);
        for (unsigned int k = j_val - 1; k > prev_j_val && sequence.size() < n; k--)
        {
            sequence.push_back(k);
        }
        j_index++;
        j_val = jacobsthal(j_index);
    }
    return (sequence);
}

void PmergeMe::ford_johnson_sort(std::deque<int>& arr, int& unpaired)
{
    if (arr.size() <= 1)
	{
        return ;
	}
	
    int level_unpaired = -1;
    std::deque<IntPair> pairs = make_pairs(arr, level_unpaired);
    std::deque<int> larger_elements;
    std::deque<int> smaller_elements;
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        larger_elements.push_back(pairs[i].first);
        smaller_elements.push_back(pairs[i].second);
    }
    int recursive_unpaired = -1;
    ford_johnson_sort(larger_elements, recursive_unpaired);
    
    arr.clear();
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        arr.push_back(larger_elements[i]);
    }

    if (!smaller_elements.empty())
    {
        int first_larger = larger_elements[0];
        int first_smaller = -1;
        size_t first_pair_idx = (size_t) -1;
        
        for (size_t i = 0; i < pairs.size(); i++)
        {
            if (pairs[i].first == first_larger)
            {
                first_smaller = pairs[i].second;
                first_pair_idx = i;
                break ;
            }
        }
        if (first_smaller != -1)
        {
            arr.insert(arr.begin(), first_smaller);
        }
        
        if (smaller_elements.size() > 1)
		{
			std::deque<unsigned int> jseq = jacobsthal_sequence_dq(larger_elements.size());
			std::deque<bool> inserted(pairs.size(), false);
		
			if (first_pair_idx != (size_t) -1)
				inserted[first_pair_idx] = true;
		
			for (size_t i = 0; i < jseq.size(); i++)
			{
				unsigned int larger_idx = jseq[i];
				
				if (larger_idx < larger_elements.size())
				{
					int target_larger = larger_elements[larger_idx];
					int corresponding_smaller = -1;
					size_t pair_idx = (size_t) -1;
					
					for (size_t j = 0; j < pairs.size(); j++)
					{
						if (pairs[j].first == target_larger && !inserted[j])
						{
							corresponding_smaller = pairs[j].second;
							pair_idx = j;
							break ;
						}
					}
					
					if (corresponding_smaller != -1)
					{
						size_t upper_bound_pos = 0;
						for (; upper_bound_pos < arr.size(); upper_bound_pos++)
						{
							if (arr[upper_bound_pos] == target_larger)
								break ;
						}
						
						binary_insert(arr, corresponding_smaller, upper_bound_pos);
						inserted[pair_idx] = true;
					}
				}
			}
			
			for (size_t i = 0; i < pairs.size(); i++)
			{
				if (!inserted[i])
				{
					int current_larger = pairs[i].first;
					int current_smaller = pairs[i].second;
					
					size_t upper_bound_pos = 0;
					for (; upper_bound_pos < arr.size(); upper_bound_pos++)
					{
						if (arr[upper_bound_pos] == current_larger)
							break ;
					}
					
					binary_insert(arr, current_smaller, upper_bound_pos);
				}
			}
		}
	}
	if (level_unpaired != -1)
    {
        binary_insert(arr, level_unpaired, arr.size());
    }
    unpaired = level_unpaired;
}

size_t PmergeMe::binary_insert(std::deque<int>& arr, int value, size_t upper_bound)
{
    unsigned int left = 0;
    unsigned int right = upper_bound;
    
    while (left < right)
    {
        unsigned int mid = left + (right - left) / 2;
        _comparisonCounter++;
        if (arr[mid] <= value)
            left = mid + 1;
        else
            right = mid;
    }
    arr.insert(arr.begin() + left, value);
    return (left);
}

void PmergeMe::sorter_vec()
{
    std::vector<int> working_copy = _vector;
    _comparisonCounter = 0;

    int unpaired = -1;
    ford_johnson_sort(working_copy, unpaired);

    _vector = working_copy;
}

void PmergeMe::sorter_dq()
{
    std::deque<int> working_copy = _deque;
    _comparisonCounter = 0;

    int unpaired = -1;
    ford_johnson_sort(working_copy, unpaired);

    _deque = working_copy;
}
std::ostream& operator<<(std::ostream& os, const PmergeMe::IntPair& pair)
{
    os << "(" << pair.first << ", " << pair.second << ", " << pair.original_index << ")";
    return (os);
}

bool PmergeMe::is_sorted() const
{
    if (_vector.size() <= 1)
        return (true);
    
    for (size_t i = 0; i < _vector.size() - 1; i++)
    {
        if (_vector[i] > _vector[i + 1])
        {
            std::cout << "Error: Array not sorted at positions " << i 
                      << " and " << i + 1 << ": " << _vector[i] 
                      << " > " << _vector[i + 1] << std::endl;
            return (false);
        }
    }
    return (true);
}



