/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:49:12 by juitz             #+#    #+#             */
/*   Updated: 2025/02/21 17:56:46 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

BitCoinExchange::BitCoinExchange()
{
	std::cout << "BitCoinExchange default constructor called" << std::endl;
}

BitCoinExchange::BitCoinExchange(const std::map <std::string, double> &data) : _data(data)
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

std::map<std::string, double> BitCoinExchange::data_to_map(const std::string &filename)
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
		double value;
		
		if (getline(ss, key, ',') && ss >> value && firstLine == false)
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
			_data[key] = value;
			continue ;
		}
		if (!is_date_valid(key) && firstLine == false)
		{
			std::cout << "Error: Date not valid." << std::endl;
			continue ;
		}
		else if (firstLine == false)
		{
		 	std::cout << "Error: invalid line format: " << line << std::endl;
		}
		firstLine = false;
	}
	return (_data);
}

bool BitCoinExchange::is_date_valid(const std::string date)
{
	if (date.size() != 11 || date[4] != '-' || date[7] != '-')
		return (false);

	for (int i = 0; i <= 11; ++i)
	{
		if (date[4] || date[7])
			continue ;
		if (!std::isdigit(date[i]))
			return (false);
	}

	//int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
/* 	bool isLeapYear;
	if (year % 4 == 0 && (year % 100 != 0) && year % 400 != 0)
		isLeapYear = true; */
	return (true);
}

std::multimap<std::string, double> BitCoinExchange::input_to_map(const std::string &filename)
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
			std::cout << key << std::endl;
			//std::cout << key.size() << std::endl;
			if (!is_date_valid(key) && firstLine == false)
			{
				std::cout << "Error: Date not valid." << std::endl;
				continue ;
			}
            _input.insert(std::make_pair(key, static_cast<double>(value)));
        }
        else if (!firstLine)
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
        firstLine = false;
    }
    return (_input);
}


