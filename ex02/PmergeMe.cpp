/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:09:20 by juitz             #+#    #+#             */
/*   Updated: 2025/06/02 16:46:00 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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

// void PmergeMe::sort_pairs(std::vector<IntPair>& pairs)
// {
//     std::sort(pairs.begin(), pairs.end());/* , [](const IntPair& a, const IntPair& b)  */
// }

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
/* 	for (size_t i = 0; i < sequence.size(); i++)
		std::cout << sequence[i];
	std::cout << std::endl; */
    return (sequence);
}
/* 
void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
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

    std::vector<int> unsorted_larger = larger_elements;
    
    int recursive_unpaired = -1;
    ford_johnson_sort(larger_elements, recursive_unpaired);
    
    // Track both the value and its original index to handle duplicates
    std::vector<std::pair<int, size_t> > value_index_pairs;
    for (size_t i = 0; i < unsorted_larger.size(); i++) {
        value_index_pairs.push_back(std::make_pair(unsorted_larger[i], i));
    }
    
    // Create mapping from original index to position in sorted array
    std::vector<size_t> index_to_position(pairs.size());
    std::vector<bool> mapped(pairs.size(), false);
    
    for (size_t i = 0; i < larger_elements.size(); i++) {
        for (size_t j = 0; j < value_index_pairs.size(); j++) {
            if (larger_elements[i] == value_index_pairs[j].first && !mapped[value_index_pairs[j].second]) {
                index_to_position[value_index_pairs[j].second] = i;
                mapped[value_index_pairs[j].second] = true;
                break;
            }
        }
    }
    
    arr.clear();
    for (size_t i = 0; i < larger_elements.size(); i++) {
        arr.push_back(larger_elements[i]);
    }

    if (!smaller_elements.empty()) {
        binary_insert(arr, smaller_elements[0], 1);
        
        // Update positions after insertion
        for (size_t i = 0; i < index_to_position.size(); i++) {
            if (index_to_position[i] >= 1)
                index_to_position[i]++;
        }
        
        if (smaller_elements.size() > 1) {
            std::vector<unsigned int> jseq = jacobsthal_sequence(smaller_elements.size());
            std::vector<bool> inserted(smaller_elements.size(), false);
            inserted[0] = true;
            
            // Insert remaining elements using Jacobsthal sequence
            for (size_t i = 0; i < jseq.size() && i < smaller_elements.size(); i++) {
                unsigned int idx = jseq[i];
                if (idx < smaller_elements.size() && !inserted[idx]) {
                    size_t insert_pos = index_to_position[idx];
                    binary_insert(arr, smaller_elements[idx], insert_pos);
                    
                    // Update positions after insertion
                    for (size_t j = 0; j < index_to_position.size(); j++) {
                        if (index_to_position[j] >= insert_pos)
                            index_to_position[j]++;
                    }
                    
                    inserted[idx] = true;
                }
            }
            
            // Insert any remaining elements
            for (size_t i = 1; i < smaller_elements.size(); i++) {
                if (!inserted[i]) {
                    binary_insert(arr, smaller_elements[i], arr.size());
                    inserted[i] = true;
                }
            }
        }
    }
    
    // Insert unpaired element if it exists
    if (level_unpaired != -1) {
        binary_insert(arr, level_unpaired, arr.size());
    }
    
    unpaired = level_unpaired;
} */

/* void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
{
    if (arr.size() <= 1)
        return;

    int level_unpaired = -1;
    std::vector<IntPair> pairs = make_pairs(arr, level_unpaired);

    std::vector<int> larger_elements;
    std::vector<int> smaller_elements;
    std::vector<size_t> pair_indices;
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        larger_elements.push_back(pairs[i].first);
        smaller_elements.push_back(pairs[i].second);
        pair_indices.push_back(pairs[i].original_index);
    }

    std::vector<int> unsorted_larger = larger_elements;
    
    int recursive_unpaired = -1;
    
    ford_johnson_sort(larger_elements, recursive_unpaired);
    
    // Create a mapping from original unsorted elements to their sorted positions
    std::vector<size_t> original_to_sorted_positions(larger_elements.size());
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        for (size_t j = 0; j < unsorted_larger.size(); j++)
        {
            if (larger_elements[i] == unsorted_larger[j])
            {
                original_to_sorted_positions[j] = i;
                break ;
            }
        }
    }
    
    arr.clear();
    // Add all larger elements to the result array
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        arr.push_back(larger_elements[i]);
    }

    if (!smaller_elements.empty())
    {
        // Insert the first smaller element at position 0
        binary_insert(arr, smaller_elements[0], 1);
        
        // Update positions of larger elements after insertion
        for (size_t i = 0; i < original_to_sorted_positions.size(); i++)
        {
            if (original_to_sorted_positions[i] >= 1)
            {
                original_to_sorted_positions[i]++;
            }
        }
        
        if (smaller_elements.size() > 1)
        {
            std::vector<unsigned int> jseq = jacobsthal_sequence(smaller_elements.size());
            std::vector<bool> inserted(smaller_elements.size(), false);
            inserted[0] = true;
            
            // Insert remaining elements according to Jacobsthal sequence
            for (size_t i = 0; i < jseq.size() && i < smaller_elements.size(); i++)
            {
                unsigned int idx = jseq[i];
                if (idx < smaller_elements.size() && !inserted[idx])
                {
                    // Find the position of the corresponding larger element
                    size_t larger_pos = original_to_sorted_positions[idx];
                    
                    // Insert the smaller element
                    binary_insert(arr, smaller_elements[idx], larger_pos + 1);
                    
                    // Update positions of all larger elements after this insertion
                    for (size_t j = 0; j < original_to_sorted_positions.size(); j++)
                    {
                        if (original_to_sorted_positions[j] >= larger_pos + 1)
                        {
                            original_to_sorted_positions[j]++;
                        }
                    }
                    
                    inserted[idx] = true;
                }
            }

            // Insert any remaining elements that weren't covered by the Jacobsthal sequence
            for (size_t i = 1; i < smaller_elements.size(); i++)
            {
                if (!inserted[i])
                {
                    binary_insert(arr, smaller_elements[i], arr.size());
                    inserted[i] = true;
                }
            }
        }
    }
    
    // Insert unpaired element if it exists
    if (level_unpaired != -1)
    {
        binary_insert(arr, level_unpaired, arr.size());
    }
    
    unpaired = level_unpaired;
} */



void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
{
    if (arr.size() <= 1)
        return;

    int level_unpaired = -1;
    std::vector<IntPair> pairs = make_pairs(arr, level_unpaired);

    std::vector<int> larger_elements;
    std::vector<int> smaller_elements;
    std::vector<size_t> original_indices;
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        larger_elements.push_back(pairs[i].first);
        smaller_elements.push_back(pairs[i].second);
        original_indices.push_back(i);
    }

    std::vector<int> unsorted_larger = larger_elements;
    std::vector<size_t> original_positions = original_indices;
    
    int recursive_unpaired = -1;
    ford_johnson_sort(larger_elements, recursive_unpaired);
    
    // Create a mapping from original positions to new positions
    std::vector<size_t> new_positions(pairs.size());
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        // Find which original pair this element came from
        for (size_t j = 0; j < unsorted_larger.size(); j++)
        {
            if (larger_elements[i] == unsorted_larger[j] && 
                (i == 0 || larger_elements[i -1] != larger_elements[i] || 
                 new_positions[original_positions[j - 1]] != i - 1))
				{
					new_positions[original_positions[j]] = i;
					break ;
				}
        }
    }
    
    arr.clear();
    // Add all larger elements to the result array
	std::cout << "Larger elements: ";
	for (size_t i = 0; i < larger_elements.size(); i++)
		std::cout << " " << larger_elements[i];
	std::cout << std::endl;
    for (size_t i = 0; i < larger_elements.size(); i++)
    {
        arr.push_back(larger_elements[i]);
    }

    // Create a positions array that maps each smaller element's original index
    // to its corresponding larger element's current position
    std::vector<size_t> positions(smaller_elements.size());
    for (size_t i = 0; i < smaller_elements.size(); i++)
    {
        positions[i] = new_positions[i];
    }

    if (!smaller_elements.empty())
    {
        // Insert first smaller element
        binary_insert(arr, smaller_elements[0], 1);
        
        // Update positions after inserting the first element
        for (size_t i = 0; i < positions.size(); i++)
        {
            if (positions[i] >= 1)
                positions[i]++;
        }
        
        if (smaller_elements.size() > 1)
        {
            std::vector<unsigned int> jseq = jacobsthal_sequence(smaller_elements.size());
            std::vector<bool> inserted(smaller_elements.size(), false);
            inserted[0] = true;
            
            // Process elements according to Jacobsthal sequence
            for (size_t i = 0; i < jseq.size() && i < smaller_elements.size(); i++)
            {
                unsigned int idx = jseq[i];
                if (idx < smaller_elements.size() && !inserted[idx])
                {
                    // Get the position where this smaller element should be inserted
                    size_t insert_pos = positions[idx];
                    
                    // Insert the smaller element
                    binary_insert(arr, smaller_elements[idx], insert_pos);
                    
                    // Update positions after insertion
                    for (size_t j = 0; j < positions.size(); j++)
                    {
                        if (positions[j] >= insert_pos)
                            positions[j]++;
                    }
                    
                    inserted[idx] = true;
                }
            }
            
            // Insert any remaining elements
            for (size_t i = 1; i < smaller_elements.size(); i++)
            {
                if (!inserted[i])
                {
                    binary_insert(arr, smaller_elements[i], arr.size());
                    inserted[i] = true;
                }
            }
        }
    }
    
    // Insert unpaired element if it exists
    if (level_unpaired != -1)
    {
        binary_insert(arr, level_unpaired, arr.size());
    }
    
    unpaired = level_unpaired;
}

/* void PmergeMe::binary_insert(std::vector<int>& arr, int value, 
                             unsigned int lower_bound, unsigned int upper_bound)
{
	upper_bound = std::min(upper_bound, (unsigned int)arr.size());
    unsigned int left = lower_bound;
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
    int recursive_unpaired = -1;
    ford_johnson_sort(larger_elements, recursive_unpaired);

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
            std::vector<bool> inserted(smaller_elements.size(), false);
            inserted[0] = true;
            
            for (size_t i = 1; i < jseq.size() && i < smaller_elements.size(); i++)
            {
                unsigned int idx = jseq[i];
                if (idx < smaller_elements.size() && !inserted[idx])
                {
                    unsigned int larger_pos = idx;
                    for (unsigned int j = 0; j < arr.size(); j++)
                    {
                        if (arr[j] == larger_elements[larger_pos])
                        {
                            binary_insert(arr, smaller_elements[idx], j + 1);
                            break;
                        }
                    }
                    inserted[idx] = true;
                }
            }

            for (size_t i = 1; i < smaller_elements.size(); i++)
            {
                if (!inserted[i])
                {
                    binary_insert(arr, smaller_elements[i], arr.size());
                    inserted[i] = true;
                }
            }
        }
    }
    
    if (level_unpaired != -1)
    {
        binary_insert(arr, level_unpaired, arr.size());
    }
    unpaired = level_unpaired;
} */

/* void PmergeMe::ford_johnson_sort(std::vector<int>& arr, int& unpaired)
{
    if (arr.size() <= 1)
        return;

    std::vector<IntPair> pairs = make_pairs(arr, unpaired);

    std::vector<int> larger_elements;
    std::vector<int> smaller_elements;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        larger_elements.push_back(pairs[i].first);
        smaller_elements.push_back(pairs[i].second);
    }

    ford_johnson_sort(larger_elements, unpaired);

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
            std::vector<bool> inserted(smaller_elements.size(), false);
			unsigned int last_inserted = 0;

			for (size_t i = 1; i < jseq.size() && i < smaller_elements.size(); i++)
			{
				unsigned int idx = jseq[i];
				if (idx < smaller_elements.size() && !inserted[idx])
				{
					unsigned int upper_bound = (jseq[i] < arr.size()) ? jseq[i] : arr.size();
					binary_insert(arr, smaller_elements[idx], upper_bound);
					inserted[idx] = true;
					last_inserted = upper_bound; // Track the last inserted position
				}
			}

			// Insert any remaining smaller elements
			for (size_t i = 0; i < smaller_elements.size(); i++)
			{
				if (!inserted[i])
				{
					binary_insert(arr, smaller_elements[i], last_inserted);
					inserted[i] = true;
				}
			}
			for (size_t i = 1; i < jseq.size() && i < smaller_elements.size(); i++)
			{
				unsigned int idx = jseq[i];
				if (idx < smaller_elements.size() && !inserted[idx])
				{
					// Use a more precise upper bound for binary search
					unsigned int upper_bound = (jseq[i] < arr.size()) ? jseq[i] : arr.size();
					binary_insert(arr, smaller_elements[idx], upper_bound);
					inserted[idx] = true;
					//last_inserted = upper_bound;
				}
			}

			// Insert any remaining smaller elements
			for (size_t i = 1; i < smaller_elements.size(); i++)
			{
				if (!inserted[i])
				{
					binary_insert(arr, smaller_elements[i], arr.size());
					inserted[i] = true;
				}
			}
        }
    }
	if (unpaired != -1 && std::find(smaller_elements.begin(), smaller_elements.end(), unpaired) == smaller_elements.end())
	{
		binary_insert(arr, unpaired, arr.size());
	}
} */

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

    int unpaired = -1;
    ford_johnson_sort(working_copy, unpaired);

    _vector = working_copy;
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



