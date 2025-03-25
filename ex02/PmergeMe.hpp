/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:55:27 by juitz             #+#    #+#             */
/*   Updated: 2025/03/25 15:59:26 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <climits>
#include <array>

class PmergeMe
{
	private:
		//std::string rawInput;
		std::array<int> _vector;
		bool _error;
	public:
		PmergeMe();
		PmergeMe(std::stack<int> &stack);
		~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
		PmergeMe operator+(const PmergeMe &other) const;
		PmergeMe operator-(const PmergeMe &other) const;
		PmergeMe operator*(const PmergeMe &other) const;
		PmergeMe operator/(const PmergeMe &other) const;

		void num_to_stack(const std::string &input);
		void parse_input(const std::string &input);
		int calculate(const std::string &input);

		bool getError() const;
	/* 	const std::string getRawInput() const;
		void setRawInput(const std::string &input); */
		//std::stack getStack() const;
};