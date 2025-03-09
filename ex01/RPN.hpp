/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:40:39 by juitz             #+#    #+#             */
/*   Updated: 2025/03/09 19:11:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
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

		int calculate(const std::string &input);
		const std::string getRawInput() const;
		void setRawInput(const std::string &input);
		//std::stack getStack() const;
};