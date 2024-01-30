#pragma once

#include <iostream>
#include <string>

class InterfaceFormatter
{
public:
	virtual void sortString(std::string& input_string) = 0;

	virtual void repalceEven(std::string& input_string) = 0;
};

class InterfaceChecker
{
public:
	virtual bool checkLength(std::string const& input_string) = 0;

	virtual bool checkForDigits(std::string const& input_string) = 0;
};

class InterfaceAdder
{
public:
	virtual bool sum(std::string& input_string) = 0;
};