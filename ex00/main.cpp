/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:09:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/17 16:28:45 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"
#include <fstream>
#include <map>
#include <string>

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	/* if (argc !=2)
		std::cout << "Error: could not open file." << std::endl; */
	BitCoinExchange BCE;
	BCE.parse_data("data.csv");
	if (!BCE._data.empty())
	{
		std::map<std::string, int>::iterator it = BCE._data.begin();
		std::cout << "First pair: " << it->first << " => " << it->second << std::endl;
	}
	else 
	{
		std::cout << "The map is empty" << std::endl;
	}
	return (0);
}