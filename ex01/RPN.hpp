/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:40:39 by juitz             #+#    #+#             */
/*   Updated: 2025/03/08 16:44:36 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stack>

class RPN
{
	private:
		std::stack<int> _stack;
	public:
		RPN();
		~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);

		int calculate(const std::string &input);
};