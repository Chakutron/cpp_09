#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define VIOLET "\e[35m"
#define CYAN "\e[36m"
#define NC "\e[0m"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange &operator=(BitcoinExchange  const &other);
		~BitcoinExchange();

		void	parseInputDB(std::string inputDB);
	private:
		std::map<std::string, std::string> _DB;
		int		checkNumber(std::string const &str);
};