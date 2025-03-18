/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:38 by codespace         #+#    #+#             */
/*   Updated: 2025/03/18 14:18:59 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: ./RPN <mathematical expression>" << std::endl;
		return (1);
	}
	RPN rpn;
	rpn.setRawInput(argv[1]);
	std::cout << rpn.getRawInput() << std::endl;
	return (0);
}