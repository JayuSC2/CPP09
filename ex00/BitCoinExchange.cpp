/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:49:12 by juitz             #+#    #+#             */
/*   Updated: 2025/02/17 16:29:11 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <string>


BitCoinExchange::BitCoinExchange()
{
	std::cout << "BitCoinExchange default constructor called" << std::endl;
}

BitCoinExchange::BitCoinExchange(const std::map <std::string, int> &data) : _data(data)
{
	std::cout << "BitCoinExchange parameterized constructor called" << std::endl;
}

BitCoinExchange::BitCoinExchange(const BitCoinExchange &copy)
{
	this->_data = copy._data;
}

BitCoinExchange &BitCoinExchange::operator=(const BitCoinExchange &other)
{
	if (this != &other)
	{
		this->_data = other._data;
	}	
	std::cout << "BitCoinExchange copy assignment operator called" << std::endl;
	return (*this);
}

BitCoinExchange::~BitCoinExchange()
{
	std::cout << "BitCoinExchange default destructor called" << std::endl;
}

std::map<std::string, int> BitCoinExchange::parse_data(const std::string &filename)
{
	std::ifstream inFile(filename.c_str());
	if (!inFile)
	{
		std::cout << "Error: could not open file " << filename << std::endl;
		return (_data);
	}
	
	std::string line;
	while (std::getline(inFile, line))
	{
		std::istringstream ss(line);
		std::string key;
		int value;
		
		if (getline(ss, key, ',') && ss >> value)
			_data[key] = value;
		else
		 	std::cout << "Error: invalid line format: " << line << std::endl;
	}
	return (_data);
}

