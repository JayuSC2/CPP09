/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:40:39 by juitz             #+#    #+#             */
/*   Updated: 2025/05/19 15:09:39 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <stack>
#include <climits>
#include <list>

class RPN
{
	private:
		std::stack<float, std::list<float> > _stack;
		bool _error;
	public:
		RPN();
		RPN(std::stack<float, std::list<float> > &stack);
		~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
		RPN operator+(const RPN &other) const;
		RPN operator-(const RPN &other) const;
		RPN operator*(const RPN &other) const;
		RPN operator/(const RPN &other) const;

		void num_to_stack(const std::string &input);
		void parse_input(const std::string &input);
		double calculate(const std::string &input);

		bool getError() const;
	/* 	const std::string getRawInput() const;
		void setRawInput(const std::string &input); */
		//std::stack getStack() const;
};