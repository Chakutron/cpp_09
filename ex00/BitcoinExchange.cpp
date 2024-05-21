#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::string	line;
	std::ifstream db("data.csv");

	//read and ignore the first line
	getline(db, line);

	while (getline(db, line))
		_DB.insert(std::pair<std::string, std::string>(line.substr(0, line.find(',')), line.substr(line.find(',') + 1, line.length())));
	db.close();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) : _DB(other._DB)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange  const &other)
{
	if (this != &other)
		this->_DB = other._DB;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{}

void	BitcoinExchange::parseInputDB(std::string inputDB)
{
	std::string line;
	std::ifstream db(inputDB.c_str());

	if (!db.is_open())
	{
		std::cout << "Error: cant open the file => " << RED << inputDB << NC << std::endl;
		return ;
	}
    else if (db.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "Error: file is empty => " << RED << inputDB << NC << std::endl;
        return ;
    }

	//checking the header
	getline(db, line);
	if (line != "date | value")
		std::cout << "Error: bad format in header => " << RED << line << NC << std::endl;

	size_t		separator;
	std::string	date;
	std::string	year;
	std::string	month;
	std::string	day;
	std::string	value;

	while(getline(db, line))
	{
		// checking if has separator
		separator = line.find('|');
		if (separator == std::string::npos || separator < 6)
		{
			std::cout << "Error: bad input => " << RED << line << NC << std::endl;
			continue ;
		}
		// checking the input date
		date = line.substr(0, separator - 1);
		year = line.substr(0, line.find('-'));
		line.erase(0, year.length() + 1);
		if (year.size() < 1)
		{
			std::cout << "Error: bad date => " << RED << date << NC << std::endl;
			continue ;
		}
		month = line.substr(0, line.find('-'));
		line.erase(0, month.length() + 1);
		if ((month.size() < 1) || (std::atoi(month.c_str()) > 12))
		{
			std::cout << "Error: bad date => " << RED << date << NC << std::endl;
			continue ;
		}
		day = line.substr(0, line.find('|') - 1);
		line.erase(0, day.length());
		if ((day.size() < 1) || (std::atoi(day.c_str()) > 31))
		{
			std::cout << "Error: bad date => " << RED << date << NC << std::endl;
			continue ;
		}
		separator = line.find('|');
		line.erase(0, separator + 2);
		// checking the value
		value = line.substr(0, line.length());
		if (value.size() == 0)
		{
			std::cout << "Error: value missing" << std::endl;
			continue ;
		}
		else if (!checkNumber(value))
		{
			std::cout << "Error: not a number" << std::endl;
			continue ;
		}
		if (std::atof(value.c_str()) <= 0)
		{
			std::cout << "Error: not a positive number" << std::endl;
			continue ;
		}
		else if (std::atof(value.c_str()) >= 1000)
		{
			std::cout << "Error: too large number" << std::endl;
			continue ;
		}
		// looking in the _DB for the closest date
		int	y1, y2, m1, m2, d1, d2;
		y1 = std::atoi(year.c_str());
		m1 = std::atoi(month.c_str());
		d1 = std::atoi(day.c_str());
		std::map<std::string, std::string>::iterator it;
		int	index;

		index = 0;
		for (it = _DB.begin(); it != _DB.end(); it++)
		{
			y2 = std::atoi((it->first.substr(0, 4)).c_str());
			m2 = std::atoi(it->first.substr(5, 2).c_str());
			d2 = std::atoi(it->first.substr(8, 2).c_str());
			if (y1 < y2)
				break ;
			else if ((y1 == y2) && (m1 < m2))
				break ;
			else if ((y1 == y2) && (m1 == m2) && d1 < d2)
				break ;
			index++;
		}
		if (index)
		{
			it--;
			std::cout << date << " => " << value << " = " << GREEN << std::atof(value.c_str()) * std::atof((it->second).c_str()) << NC << std::endl;
		}
		else
			// date is lower than the first date in _DB
			std::cout << date << " => " << value << " = " << GREEN << "0 (first date in database: " << it->first << ")" << NC << std::endl;
	}
	db.close();
}

int	BitcoinExchange::checkNumber(std::string const &str)
{
	int	i = 0;
	int	n = 0;
	int	d = 0;
	int s = 0;

	if (!str.size())
		return (0);
	if (str[i] == '-')
	{
		n++;
		i++;
	}
	while (i < static_cast<int>(str.size()))
	{
		if (str[i] == '-')
			n++;
		else if (str[i] == '.' && str[i - 1] >= 48 && str[i - 1] <= 57)
			s++;
		else if (str[i] >= 48 && str[i] <= 57)
			d++;
		i++;
	}
	if (n <= 1 && s <= 1 && str[i - 1] >= 48 && str[i - 1] <= 57 && static_cast<int>(str.size()) == (n + d + s))
		return (1);
	return (0);
}