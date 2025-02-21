/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:57:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/21 17:50:52 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>

class BitCoinExchange
{
/* 	private:
		std::map<std::string, int> _data;
		std::multimap<std::string, int> _input; */
	
	public:
		std::map<std::string, double> _data;
		std::multimap<std::string, double> _input;
		BitCoinExchange();
		BitCoinExchange(const std::map<std::string, double> &data);
		~BitCoinExchange();
		BitCoinExchange(const BitCoinExchange &copy);
		BitCoinExchange &operator=(const BitCoinExchange &other);

		std::map<std::string, double> data_to_map(const std::string &filename);
		std::multimap<std::string, double> input_to_map(const std::string &filename);
		bool is_date_valid(const std::string date);
	
};