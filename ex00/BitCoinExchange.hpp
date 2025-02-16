/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juitz <juitz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:57:49 by juitz             #+#    #+#             */
/*   Updated: 2025/02/16 16:19:44 by juitz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>

class BitCoinExchange
{
	private:
		std::string *dataarray;
	public:
		BitCoinExchange();
		
		~BitCoinExchange();
};