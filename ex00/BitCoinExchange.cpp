/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:49:12 by juitz             #+#    #+#             */
/*   Updated: 2025/06/23 16:45:14 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"
#include <cctype>


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

const std::map<std::string, double>& BitCoinExchange::getData() const
{
	return (_data);
}

const std::multimap<std::string, double>& BitCoinExchange::getInput() const
{
	return (_input);
}

const char* BitCoinExchange::FileDoesntExist::what() const throw()
{
   return ("Error: could not open file ");
}

std::map<std::string, double> BitCoinExchange::data_to_map(const std::string &filename)
{
	std::ifstream inFile(filename.c_str());
	if (!inFile)
	{
		throw FileDoesntExist();
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

double BitCoinExchange::getExchangeRate(const std::string &date)
{
    if (_data.find(date) != _data.end())
        return (_data[date]);
    
    std::map<std::string, double>::iterator it = _data.lower_bound(date);
    if (it == _data.begin() && date < it->first) 
	{
        std::cout << "Error: no data available for date " << date << std::endl;
        return (-1);
    }
    
    if (it != _data.begin() && (it == _data.end() || it->first > date))
	{
		//std::cout << "no data availale for date " << date << ", using most recent available data: " << (--it)->first << std::endl;
        --it;
	}
    return (it->second);
}

bool BitCoinExchange::is_date_valid(const std::string date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	for (int i = 0; i <= 11; ++i)
	{
		if (date[4] || date[7])
			continue ;
		if (!std::isdigit(date[i]))
			return (false);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	bool isLeapYear = false;
	if (year % 4 == 0 && (year % 100 != 0) && year % 400 != 0)
		isLeapYear = true;
	if (month == 2 && day > 28 && isLeapYear == false)
		return (false);
	if (month == 2 && day > 29 && isLeapYear == true)
		return (false);
	return (true);
}
int findChar(const std::string& str, char c)
{
    std::string::const_iterator it = std::find(str.begin(), str.end(), c);
    if (it != str.end())
        return (static_cast<int>(it - str.begin()));
    return (-1);
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
        std::string dateStr;
        double value;

        if (std::getline(ss, dateStr, '|') && ss >> value)
        {
			if (!isdigit(line[0]))
			{
				std::cout << "Error: first char has to be a digit => " << line << std::endl;
				continue ;
			}
			int pipe_pos = findChar(line, '|');
			if (line[pipe_pos - 1] != ' ' || line[pipe_pos + 1] != ' ')
			{
				std::cout << "Error: bad input => " << line << std::endl;
				continue ;
			}
		    bool value_is_valid = true;
            bool period_found = false;
            std::string value_part = line.substr(pipe_pos + 1);
            value_part.erase(0, value_part.find_first_not_of(" \t"));

            for (size_t i = 0; i < value_part.length(); ++i)
            {
                if (isdigit(value_part[i]))
                {
                    continue ;
                }
                else if (value_part[i] == '.' && !period_found)
                {
                    period_found = true;
                }
                else
                {
                    value_is_valid = false;
                    break ;
                }
            }

            if (!value_is_valid)
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue ;
            }
			dateStr.erase(0, dateStr.find_first_not_of(" \t"));
            dateStr.erase(dateStr.find_last_not_of(" \t") + 1);
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
			if (!is_date_valid(dateStr) && firstLine == false)
			{
				std::cout << "Error: Date not valid." << std::endl;
				continue ;
			}
            _input.insert(std::make_pair(dateStr, static_cast<double>(value)));
			
			double exchangeRate = getExchangeRate(dateStr);
            if (exchangeRate >= 0)
                std::cout << dateStr << " => " << value << " = " << (value * exchangeRate) << std::endl;
			
        }
        else if (!firstLine)
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
        firstLine = false;
    }
    return (_input);
}

/* std::multimap<std::string, double> BitCoinExchange::input_to_map(const std::string &filename)
{
    std::ifstream inFile(filename.c_str());
    if (!inFile)
    {
        std::cout << "Error: could not open file " << filename << std::endl;
        return (_input);
    }
	std::string line;
    if (!std::getline(inFile, line))
	{
        return (_input); 
    }

    while (std::getline(inFile, line))
    {
        size_t pipe_pos = line.find('|');
        if (pipe_pos == std::string::npos)
		{
            std::cout << "Error: bad input => " << line << std::endl;
            continue ;
        }

        std::string dateStr = line.substr(0, pipe_pos);
        std::string valueStr = line.substr(pipe_pos + 1);

        dateStr.erase(0, dateStr.find_first_not_of(" \t"));
        dateStr.erase(dateStr.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

        if (!is_date_valid(dateStr))
		{
            std::cout << "Error: bad date => " << dateStr << std::endl;
            continue ;
        }

        char* end;
        double value = std::strtod(valueStr.c_str(), &end);
        if (*end != '\0' || valueStr.empty())
		{
            std::cout << "Error: value is not a valid number => " << valueStr << std::endl;
            continue ;
        }
        if (value < 0)
		{
            std::cout << "Error: not a positive number." << std::endl;
            continue ;
        }
        if (value > 1000)
		{ 
            std::cout << "Error: too large a number." << std::endl;
            continue ;
        }
        double exchangeRate = getExchangeRate(dateStr);
        if (exchangeRate >= 0)
		{
            std::cout << dateStr << " => " << value << " = " << (value * exchangeRate) << std::endl;
        }
    }
    return (_input);
} */


