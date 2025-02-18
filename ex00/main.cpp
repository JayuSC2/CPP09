/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:09:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/18 17:42:48 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"
#include <fstream>
#include <map>
#include <string>

int main(int argc, char **argv)
{
	if (argc !=2)
		std::cout << "Error: could not open file." << std::endl;
	BitCoinExchange BCE;
/* 	BCE.data_to_map("data.csv");
	if (!BCE._data.empty())
	{
		std::map<std::string, int>::iterator it = BCE._data.begin();
		std::cout << "First pair: " << it->first << " => " << it->second << std::endl;
	}
	else 
	{
		std::cout << "The map is empty" << std::endl;
	} */
	std::string filename = argv[1];
	BCE.input_to_map(filename);
	if (!BCE._input.empty())
	{
		std::map<std::string, int>::iterator it = BCE._input.begin();
		std::cout << "First pair: " << it->first << " => " << it->second << std::endl;
	}
	return (0);
}