#include "UserStringHandler.h"
#include <algorithm>
#include <mutex>

void UserStringHandler::sort()
{
	std::sort(data.rbegin(), data.rend());
}

void UserStringHandler::replceEven()
{
	std::string replacement_substring = "KB";
	std::string temp = data;
	int i = 0;
	while (i < data.length())
	{
		std::string replacable_substring = data.substr(i, 1);

		if (replacable_substring != "B" && std::stoll(replacable_substring) % 2 == 0)
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

void UserStringHandler::writeIntoBuffer(Buffer& buffer)
{
	std::unique_lock<std::mutex> locker(buffer.buffer_mtx);
	buffer.data = data;
	buffer.is_filled = true;
	buffer.buffer_check.notify_one();
}

void UserStringHandler::doTask(Buffer& buffer)
{
	while (true)
	{
		{
			std::scoped_lock lock(buffer.console_mtx);
			std::cout << "Enter string: ";
			std::cin >> data;
		}
		if (checkLength() && checkForDigits())
		{
			sort();
			checkForDigits();
			replceEven();
			writeIntoBuffer(buffer);
			data.clear();
		}
	}
}
