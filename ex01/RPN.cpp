/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:45:01 by juitz             #+#    #+#             */
/*   Updated: 2025/03/21 16:42:29 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>

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

void RPN::num_to_stack(const std::string &input)
{
	std::istringstream iss(input);
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(token[0]))
		{
			int num = token[0] - '0';
			_stack.push(num);
		}
		else if (token.size() == 1 && token[0] == '+' || token[0] == '-' || token[0] == '/' || token[0] == '*')
		{
			if (token.size() < 2)
			{
				throw std::runtime_error("Not enough operands for amount of operators");
			}

			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			
			switch (token[0])
			{
				case '+':
					_stack.push(a + b);
					break;
				case '-':
					_stack.push(a - b);
					break;
				case '*':
					_stack.push(a * b);
					break;
				case '/':
					if (b == 0)
						throw std::runtime_error("Error: Can't divide by 0");
					_stack.push(a / b);
					break;
			}
		}
		else
		{
			throw std::runtime_error("Error: invalid token: " + token);
		}
	}
}
		
void RPN::parse_input(const std::string &input)
{
	
}

int RPN::calculate(const std::string &input)
{
	int result;
	
}