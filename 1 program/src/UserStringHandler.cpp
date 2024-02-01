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

void UserStringHandler::writeIntoBuffer(std::string& buffer, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled)
{
	buffer = data;
	is_filled = true;
}

void UserStringHandler::doTask(std::string& buffer, std::mutex& console_mtx, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled)
{
	while (true)
	{
		{
			std::scoped_lock lock(console_mtx);
			std::cout << "Enter string: ";
			std::cin >> data;
		}
		if (checkLength() && checkForDigits())
		{
			sort();
			checkForDigits();
			replceEven();
			{
				std::unique_lock<std::mutex> locker(buffer_mtx);
				writeIntoBuffer(buffer, buffer_mtx, buffer_check, is_filled);
				buffer_check.notify_one();
				buffer_check.wait(locker, [&is_filled] { return !is_filled; });
			}
			data.clear();
		}
	}
}