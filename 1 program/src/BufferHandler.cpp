#include "BufferHandler.h"

void BufferHandler::readFromBuffer(std::string& buffer, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled)
{
	this->data = std::move(buffer);
	is_filled = false;
	//buffer_check.notify_one();
}

void BufferHandler::sum()
{
	int begin_of_number = 0;
	int length_of_number = 0;
	std::string number;
	for (int i = 0; i < data.length(); i++)
	{
		if (data[i] == 'B')
		{
			begin_of_number = i + 1;
			if (data.find("K", i) == std::string::npos) //check whether there is K after B 
				length_of_number++;						//if not - length_of_number = 1
		}
		else if (data[i] == 'K' || i == data.length() - 1)
		{
			length_of_number += i - begin_of_number;
			number = data.substr(begin_of_number, length_of_number);
			if (length_of_number != 0)
				this->sum_of_numbers += std::stoi(number);
			length_of_number = 0;
		}
	}
}

void BufferHandler::writeData(std::mutex& console_mtx)
{
	std::scoped_lock lock(console_mtx);
	std::cout << "Recieved data is: " << data << " sum is: " << sum_of_numbers << std::endl;
}

void BufferHandler::sendData()
{
	sum_of_numbers = 0;
}

void BufferHandler::doTask(std::string& buffer, std::mutex& console_mtx, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled)
{
	while (true)
	{
		{
			std::unique_lock<std::mutex> locker(buffer_mtx);
			buffer_check.wait(locker, [&is_filled] { return is_filled; });
			readFromBuffer(buffer, buffer_mtx, buffer_check, is_filled);
			sum();
			writeData(console_mtx);
			buffer_check.notify_one();
		}
		sendData();
	}
}