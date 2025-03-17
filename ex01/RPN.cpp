/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:45:01 by juitz             #+#    #+#             */
/*   Updated: 2025/03/09 19:11:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
	std::cout << "RPN default constructor called" << std::endl;
}

RPN::RPN(std::stack<int> &stack) : _stack(stack)
{
	std::cout << "RPN parameterized constructor called" << std::endl;
}

RPN::RPN(const RPN &copy)
{
	this->_stack = copy._stack;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
	}	
	std::cout << "RPN copy assignment operator called" << std::endl;
	return (*this);
}

RPN::~RPN()
{
	std::cout << "RPN default destructor called" << std::endl;
}

const std::string RPN::getRawInput() const
{
	return (this->rawInput);
}

void RPN::setRawInput(const std::string &input)
{
	this->rawInput = input;
}