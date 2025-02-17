/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:09:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/17 12:48:03 by juitz            ###   ########.fr       */
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
	
	std::string filename = argv[1];
	std::ifstream inFile(filename);
	if (!inFile)
		std::cout << "Error: could not open file." << std::endl;
	std::ofstream outFile(filename + ".test");
	if (!outFile)
		std::cout << "Error: could not open file." << std::endl;
	
	std::map<std::string, int> datamap;
	std::map<std::string, int>::iterator it = datamap.begin();
	while 
}