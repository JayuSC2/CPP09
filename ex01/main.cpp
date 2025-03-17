/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:12:38 by codespace         #+#    #+#             */
/*   Updated: 2025/03/09 19:12:35 by codespace        ###   ########.fr       */
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
	return (0);
}