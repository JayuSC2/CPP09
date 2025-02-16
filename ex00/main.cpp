/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:09:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/13 17:33:32 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
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
	
	inFile.read(inFile);
}