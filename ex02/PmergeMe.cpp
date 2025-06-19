/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:20 by juitz             #+#    #+#             */
/*   Updated: 2025/06/19 19:25:00 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vector(0), _deque(0), _unpaired(0), _operationCounter(0)
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
	this->_operationCounter = copy._operationCounter;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
		this->_unpaired = other._unpaired;
		this->_operationCounter = other._operationCounter;
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
	return (_operationCounter);
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
        _operationCounter++;
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
        _operationCounter++;
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

/* std::vector<unsigned int> PmergeMe::jacobsthal_sequence(unsigned int n)
{
    std::vector<unsigned int> sequence;
    std::vector<bool> used(n, false);  // To track which indices are already in the sequence

    if (n == 0)
        return sequence;
    
    // Start with index 0 (first element is always processed first)
    sequence.push_back(0);
    used[0] = true;
    
    if (n == 1)
        return sequence;

    unsigned int j_index = 3;
    unsigned int j_val = jacobsthal(j_index);

    while (sequence.size() < n)
    {
        // Make sure to bound the Jacobsthal value
        unsigned int bounded_j_val = std::min(j_val, n - 1);
        
        // Check if we've added anything in this iteration
        bool added_any = false;
        
        if (bounded_j_val < n && !used[bounded_j_val])
        {
            sequence.push_back(bounded_j_val);
            used[bounded_j_val] = true;
            added_any = true;
        }

        unsigned int prev_j_val = jacobsthal(j_index - 1);
        
        // Generate the sequence in reverse order from current J number down to previous+1
        for (unsigned int k = bounded_j_val - 1; k > prev_j_val && k < n; k--)
        {
            if (!used[k])
            {
                sequence.push_back(k);
                used[k] = true;
                added_any = true;
            }
        }
        
        // Always increment j_index to prevent infinite loop
        j_index++;
        j_val = jacobsthal(j_index);
        
        // If we didn't add any elements in this iteration and we've tried all indices,
        // we should break to avoid an infinite loop
        if (!added_any && bounded_j_val >= n - 1)
        {
            // Add any remaining elements
            for (unsigned int i = 0; i < n; i++)
            {
                if (!used[i])
                {
                    sequence.push_back(i);
                    used[i] = true;
                }
            }
            break;
        }
        if (sequence.size() >= n)
            break;
    }
    
    return sequence;
} */

void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
{
    if (arr.size() <= 1)
        return ;

    int level_unpaired = -1;
    std::vector<IntPair> pairs = make_pairs(arr, level_unpaired);

    std::vector<int> larger_elements;
    std::vector<int> smaller_elements;
    
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
            //_operationCounter++;
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
            std::vector<unsigned int> jseq = jacobsthal_sequence_vec(smaller_elements.size());
            std::vector<bool> inserted(pairs.size(), false);
            
            if (first_pair_idx != (size_t) -1)
                inserted[first_pair_idx] = true;
            
            for (size_t i = 0; i < jseq.size(); i++)
            {
                unsigned int idx = jseq[i];
                
                if (idx < pairs.size() && !inserted[idx])
                {
                    int current_larger = pairs[idx].first;
                    int current_smaller = pairs[idx].second;
                    
                    size_t pos = 0;
                    for (; pos < arr.size(); pos++)
                    {
                        //_operationCounter++;
                        if (arr[pos] == current_larger)
                            break ;
                    }
                    
                    if (pos < arr.size())
                    {
                        binary_insert(arr, current_smaller, pos);
                    }
                    
                    inserted[idx] = true;
                }
            }
            for (size_t i = 0; i < pairs.size(); i++)
            {
                if (!inserted[i])
                {
                    int current_larger = pairs[i].first;
                    int current_smaller = pairs[i].second;
                    
                    size_t pos = 0;
                    for (; pos < arr.size(); pos++)
                    {
                        //_operationCounter++;
                        if (arr[pos] == current_larger)
                            break ;
                    }
                    
                    if (pos < arr.size())
                    {
                        binary_insert(arr, current_smaller, pos);
                    }
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

size_t PmergeMe::binary_insert(std::vector<int>& arr, int value, unsigned int upper_bound)
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
    return (left);
}

std::vector<unsigned int> PmergeMe::jacobsthal_sequence_vec(unsigned int n)
{
    std::vector<unsigned int> sequence;

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
        return ;

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
            //_operationCounter++;
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
            std::deque<unsigned int> jseq = jacobsthal_sequence_dq(smaller_elements.size());
            std::deque<bool> inserted(pairs.size(), false);
            
            if (first_pair_idx != (size_t) -1)
                inserted[first_pair_idx] = true;
            
            for (size_t i = 0; i < jseq.size(); i++)
            {
                unsigned int idx = jseq[i];
                
                if (idx < pairs.size() && !inserted[idx])
                {
                    int current_larger = pairs[idx].first;
                    int current_smaller = pairs[idx].second;
                    
                    size_t pos = 0;
                    for (; pos < arr.size(); pos++)
                    {
                        //_operationCounter++;
                        if (arr[pos] == current_larger)
                            break ;
                    }
                    
                    if (pos < arr.size())
                    {
                        binary_insert(arr, current_smaller, pos);
                    }
                    
                    inserted[idx] = true;
                }
            }
            for (size_t i = 0; i < pairs.size(); i++)
            {
                if (!inserted[i])
                {
                    int current_larger = pairs[i].first;
                    int current_smaller = pairs[i].second;
                    
                    size_t pos = 0;
                    for (; pos < arr.size(); pos++)
                    {
                        //_operationCounter++;
                        if (arr[pos] == current_larger)
                            break ;
                    }
                    
                    if (pos < arr.size())
                    {
                        binary_insert(arr, current_smaller, pos);
                    }
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

size_t PmergeMe::binary_insert(std::deque<int>& arr, int value, unsigned int upper_bound)
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
    return (left);
}

/* void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
{
    if (arr.size() <= 1)
        return;

    int level_unpaired = -1;
    std::vector<IntPair> pairs = make_pairs(arr, level_unpaired);

    std::vector<int> larger_elements;
    std::vector<int> smaller_elements;
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        larger_elements.push_back(pairs[i].first);
        smaller_elements.push_back(pairs[i].second);
    }

    //Save a copy of the unsorted larger elements to track positions
    std::vector<int> unsorted_larger = larger_elements;
    
    //Recursively sort the larger elements
    int recursive_unpaired = -1;
    ford_johnson_sort(larger_elements, recursive_unpaired);
    
    //Clear the result array and add sorted larger elements
    arr.clear();
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        arr.push_back(larger_elements[i]);
    }

    //Create a mapping to track which smaller element corresponds to which larger element
    std::vector<std::pair<int, int> > element_pairs;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        element_pairs.push_back(std::make_pair(pairs[i].first, pairs[i].second));
    }

    if (!smaller_elements.empty())
    {
        //Insert the first smaller element
        int first_larger = larger_elements[0];
        int first_smaller = -1;
        
        //Find the smaller element that corresponds to the first larger element
        for (size_t i = 0; i < element_pairs.size(); i++)
        {
            if (element_pairs[i].first == first_larger)
            {
                first_smaller = element_pairs[i].second;
                break ;
            }
        }
        
        if (first_smaller != -1)
        {
            arr.insert(arr.begin(), first_smaller);
        }
        
        //Use Jacobsthal sequence for the rest
        if (smaller_elements.size() > 1)
        {
            std::vector<unsigned int> jseq = jacobsthal_sequence(smaller_elements.size());
            std::vector<bool> inserted(element_pairs.size(), false);
            
            //Mark the first element as inserted
            for (size_t i = 0; i < element_pairs.size(); i++)
            {
                if (element_pairs[i].first == first_larger)
                {
                    inserted[i] = true;
                    break ;
                }
            }
            
            //Insert remaining elements according to Jacobsthal sequence
            for (size_t i = 0; i < jseq.size() && i < element_pairs.size(); i++)
            {
                unsigned int idx = jseq[i];
                if (idx < element_pairs.size() && !inserted[idx])
                {
                    int current_larger = element_pairs[idx].first;
                    int current_smaller = element_pairs[idx].second;
                    
                    //Find position of the larger element in the sorted array
                    size_t pos = 0;
                    for (; pos < arr.size(); pos++)
                    {
                        if (arr[pos] == current_larger)
                            break ;
                    }
                    
                    if (pos < arr.size())
                    {
                        binary_insert(arr, current_smaller, pos);
                    }
                    
                    inserted[idx] = true;
                }
            }
            
            //Insert any remaining elements
            for (size_t i = 0; i < element_pairs.size(); i++)
            {
                if (!inserted[i])
                {
                    int current_larger = element_pairs[i].first;
                    int current_smaller = element_pairs[i].second;
                    
                    size_t pos = 0;
                    for (; pos < arr.size(); pos++)
                    {
                        if (arr[pos] == current_larger)
						{
							_operationCounter++;
							 break ;
						}
                    }
                    
                    if (pos < arr.size())
                    {
                        binary_insert(arr, current_smaller, pos);
                    }
                }
            }
        }
    }
    
    //Insert unpaired element if it exists
    if (level_unpaired != -1)
    {
        binary_insert(arr, level_unpaired, arr.size());
    }
    
    unpaired = level_unpaired;
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
} */

void PmergeMe::sorter_vec()
{
    std::vector<int> working_copy = _vector;
    _operationCounter = 0;

    int unpaired = -1;
    ford_johnson_sort(working_copy, unpaired);

    _vector = working_copy;
}

void PmergeMe::sorter_dq()
{
    std::deque<int> working_copy = _deque;
    _operationCounter = 0;

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



