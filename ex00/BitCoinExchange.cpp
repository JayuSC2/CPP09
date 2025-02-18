/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:49:12 by juitz             #+#    #+#             */
/*   Updated: 2025/02/18 18:57:31 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"


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

std::map<std::string, int> BitCoinExchange::data_to_map(const std::string &filename)
{
	std::ifstream inFile(filename.c_str());
	if (!inFile)
	{
		std::cout << "Error: could not open file " << filename << std::endl;
		return (_data);
	}
	
	std::string line;
	bool firstLine = true;
	while (std::getline(inFile, line))
	{
		std::istringstream ss(line);
		std::string key;
		unsigned int value;
		
		if (getline(ss, key, ',') && ss >> value)
			_data[key] = value;
		else if (firstLine == false)
		 	std::cout << "Error: invalid line format: " << line << std::endl;
		firstLine = false;
	}
	return (_data);
}

bool BitCoinExchange::is_date_valid(const std::string date)
{
	int i = 0;
	if ()
}

std::multimap<std::string, int> BitCoinExchange::input_to_map(const std::string &filename)
{
    std::ifstream inFile(filename.c_str());
    if (!inFile)
    {
        std::cout << "Error: could not open file " << filename << std::endl;
        return (_input);
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(inFile, line))
    {
        std::istringstream ss(line);
        std::string key;
        double value;

        if (std::getline(ss, key, '|') && ss >> value)
        {
            if (value > static_cast<double>(std::numeric_limits<int>::max()))
            {
                std::cout << "Error: too large a number." << std::endl;
                continue ;
            }
			if (value < 0) 
			{
                std::cout << "Error: not a positive number." << std::endl;
                continue ;
            }
            _input.insert(std::make_pair(key, static_cast<int>(value)));
        }
        else if (!firstLine)
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
        firstLine = false;
    }
    return (_input);
}

