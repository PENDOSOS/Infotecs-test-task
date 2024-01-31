#include "UserStringHandler.h"
#include <algorithm>
#include <mutex>

void UserStringHandler::sort()
{
	std::sort(data.begin(), data.end());
}

void UserStringHandler::replceEven()
{
	std::string replacement_substring = "KB";
	std::string temp = data;
	int i = 0;
	while (i < data.length())
	{
		std::string replacable_substring = data.substr(i, 1);

		if (replacable_substring != "B" && std::stoi(replacable_substring) % 2 == 0)
		{
			data.replace(i, 1, replacement_substring);
		}
		i++;
	}
}

bool UserStringHandler::checkLength()
{
	return data.length() <= 64;
}

bool UserStringHandler::checkForDigits()
{
	for (int i = 0; i < data.length(); i++)
	{
		if (!isdigit(data[i]))
			return false;
	}
	return true;
}

void UserStringHandler::writeIntoBuffer(std::string& buffer)
{
	buffer = data;
}

void UserStringHandler::doTask(std::string& buffer)
{
	while (true)
	{
		std::cout << "Enter string: ";
		std::cin >> data;
		if (checkLength() && checkForDigits())
		{
			sort();
			checkForDigits();
			replceEven();
			writeIntoBuffer(buffer);
			std::cout << "Buffer written" << std::endl;
			data.clear();
		}
		else if (data == "-")
			return;
		else
			std::cout << "String is incorrect" << std::endl;
	}
}