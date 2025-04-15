/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:55:27 by juitz             #+#    #+#             */
/*   Updated: 2025/04/15 18:34:35 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
#include <cstdio>
class PmergeMe
{
	private:
		//std::string rawInput;
		std::vector<int> _vector;
		unsigned int _unpaired;
		unsigned int _operationCounter;
	public:
		PmergeMe();
		explicit PmergeMe(std::vector<int> vector);
		~PmergeMe();
        explicit PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
		/* bool operator>(const PmergeMe &other) const;
		bool operator<(const PmergeMe &other) const;
		PmergeMe operator+(const PmergeMe &other) const;
		PmergeMe operator-(const PmergeMe &other) const;
		PmergeMe operator*(const PmergeMe &other) const;
		PmergeMe operator/(const PmergeMe &other) const; */
		
		const std::vector<int>& getVector() const;

		int parse_input(int argc, char **argv);
		typedef std::pair<int, int> IntPair;
		std::vector<IntPair> make_pairs(const std::vector<int>& input);
		void sort_pairs(std::vector<IntPair>& pairs);
		void sorter();
		void make_pairs();
		void sort_pairs(const std::vector<int>);

		bool getError() const;
	/* 	const std::string getRawInput() const;
		void setRawInput(const std::string &input); */
		//std::stack getStack() const;
};