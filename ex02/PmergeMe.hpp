/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:55:27 by juitz             #+#    #+#             */
/*   Updated: 2025/04/15 15:08:38 by juitz            ###   ########.fr       */
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
		unsigned int _maxCount;
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

		void make_pairs(const std::vector<int>);
		void sort_pairs(const std::vector<int>);
		int parse_input(int argc, char **argv);

		bool getError() const;
	/* 	const std::string getRawInput() const;
		void setRawInput(const std::string &input); */
		//std::stack getStack() const;
};