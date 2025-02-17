/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:57:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/17 16:26:49 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>

class BitCoinExchange
{
	//private:
	
	public:
		std::map<std::string, int> _data;
		BitCoinExchange();
		BitCoinExchange(const std::map<std::string, int> &data);
		~BitCoinExchange();
		BitCoinExchange(const BitCoinExchange &copy);
		BitCoinExchange &operator=(const BitCoinExchange &other);

		std::map<std::string, int> parse_data(const std::string &filename);
		
};