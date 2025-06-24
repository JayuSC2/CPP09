/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:09:49 by juitz             #+#    #+#             */
/*   Updated: 2025/06/23 18:49:31 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    
    BitCoinExchange BCE;
	try
	{
		BCE.data_to_map("data.csv");
		BCE.input_to_map(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
    return (0);
}

/* int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	if (argc != 2)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	BitCoinExchange BCE;
	BCE.data_to_map("data.csv");
	if (!BCE._data.empty())
	{
		std::map<std::string, double>::iterator it = BCE._data.begin();
		std::cout << "First pair: " << it->first << " => " << it->second << std::endl;
		std::cout << "test1: " << BCE._data["2013-04-21"] << std::endl;
	}
	else 
	{
		std::cout << "The map is empty" << std::endl;
	}
	std::string filename = argv[1];
	BCE.input_to_map(filename);
	double exchangeRate = BCE._data["2011-05-02"];
	double amount = BCE._input.find()
	std::cout << BCE._data["2011-05-02"]  BCE._input["2011-01-03"] << std::endl;
	if (!BCE._input.empty())
	{
		std::map<std::string, double>::iterator it = BCE._input.begin();
		std::cout << "First pair: " << it->first << " => " << it->second << std::endl;
	}
	return (0);
} */