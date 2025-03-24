/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:38 by codespace         #+#    #+#             */
/*   Updated: 2025/03/24 15:35:54 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: ./RPN \"mathematical expression\"" << std::endl;
		return (1);
	}
	RPN rpn;
	int result;
	//rpn.setRawInput(argv[1]);
	result = rpn.calculate(argv[1]);
	if (!rpn.getError())
		std::cout << result << std::endl;
	return (0);
}