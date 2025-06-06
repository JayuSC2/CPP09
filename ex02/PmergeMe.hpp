/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:55:27 by juitz             #+#    #+#             */
/*   Updated: 2025/06/04 20:10:59 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <deque>

class PmergeMe
{
	private:
		//std::string rawInput;
		std::vector<int> _vector;
		std::deque<int> _deque;
		unsigned int _unpaired;
		unsigned int _operationCounter;
		time_t _vector_time;
		time_t _deque_time;
	public:
		struct IntPair 
		{
        int first;
        int second;
		size_t index;
        int original_index;
    	};
		PmergeMe();
		explicit PmergeMe(std::vector<int> vector);
		~PmergeMe();
        explicit PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
		const std::vector<int>& get_vector() const;
		const unsigned int& get_operations() const;

		int parse_input(int argc, char **argv);
		//typedef std::pair<int, int> IntPair;
		std::vector<IntPair> make_pairs(const std::vector<int>& input, int &unpaired);
		void sort_pairs(std::vector<IntPair>& pairs);
		unsigned int jacobsthal(unsigned int n);
		std::vector<unsigned int> jacobsthal_sequence(unsigned int n);
		void ford_johnson_sort(std::vector<int>& arr, int &unpaired);
		size_t binary_insert(std::vector<int>& arr, int value, unsigned int upper_bound);
		//void binary_insert(std::vector<int>& arr, int value, unsigned int upper_bound);
		void sorter();
		//void make_pairs();
		//void sort_pairs(const std::vector<int>);
		bool is_sorted() const;
		bool getError() const;
	/* 	const std::string getRawInput() const;
		void setRawInput(const std::string &input); */
		//std::stack getStack() const;
};

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& pair);