/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:45:01 by juitz             #+#    #+#             */
/*   Updated: 2025/05/19 15:09:44 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <exception>

RPN::RPN()
{
	std::cout << "RPN default constructor called" << std::endl;
}

RPN::RPN(std::stack<float, std::list<float> > &stack) : _stack(stack), _error(false)
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

bool RPN::getError() const
{
	return (this->_error);
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
		else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '/' || token[0] == '*'))
		{
			if (_stack.size() < 2)
			{
				throw std::runtime_error("Error: not enough operands for operator");
			}

			float b = _stack.top();
			_stack.pop();
			float a = _stack.top();
			_stack.pop();
			
			switch (token[0])
			{
				case '+':
				if ((a > 0 && b > (float)INT_MAX - a) || (a < 0 && b < (float)INT_MIN - a))
					throw std::runtime_error("Error: integer overflow in addition");
				_stack.push(a + b);
				break;
			case '-':
				if ((b > 0 && a < (float)INT_MIN + b) || (b < 0 && a > (float)INT_MAX + b))
					throw std::runtime_error("Error: integer overflow in subtraction");
				_stack.push(a - b);
				break;
			case '*':
				if (a != 0 && b != 0) {
					if ((a > 0 && b > 0 && a > (float)INT_MAX / b) ||
						(a > 0 && b < 0 && b < (float)INT_MIN / a) ||
						(a < 0 && b > 0 && a < (float)INT_MIN / b) ||
						(a < 0 && b < 0 && a < (float)INT_MAX / b))
						throw std::runtime_error("Error: integer overflow in multiplication");
				}
				_stack.push(a * b);
				break;
			case '/':
				if (b == 0)
					throw std::runtime_error("Error: Can't divide by 0");
				if (a == INT_MIN && b == -1)
					throw std::runtime_error("Error: integer overflow in division");
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

double RPN::calculate(const std::string &input)
{
	while (!_stack.empty())
		_stack.pop();
	
	try
	{
		num_to_stack(input);

		if (_stack.size() != 1)
			throw std::runtime_error("Error: too many operands before operator");
		return (_stack.top());
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		_error = true;
		return (1);
	}
}