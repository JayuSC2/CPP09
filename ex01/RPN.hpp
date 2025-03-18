/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:40:39 by juitz             #+#    #+#             */
/*   Updated: 2025/03/18 14:28:13 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
	private:
		std::string rawInput;
		std::stack<int> _stack;
	public:
		RPN();
		RPN(std::stack<int> &stack);
		~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
		RPN operator+(const RPN &other) const;
		RPN operator-(const RPN &other) const;
		RPN operator*(const RPN &other) const;
		RPN operator/(const RPN &other) const;

		void num_to_stack(const std::string &input);
		void parse_input(const std::string &input);
		int calculate(const std::string &input);

		const std::string getRawInput() const;
		void setRawInput(const std::string &input);
		//std::stack getStack() const;
};