#include "BufferHandler.h"
#include "Client.h"

void BufferHandler::readFromBuffer(std::string& buffer, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled)
{
	this->data = std::move(buffer);
	is_filled = false;
}

void BufferHandler::sum()
{
	int length_of_number = 0;
	std::string number;
	while (data.length() != 0)
	{
		length_of_number = data.find("KB");
		if (length_of_number != std::string::npos)
		{
			number = data.substr(0, length_of_number);
			if (number.length() != 0)
				this->sum_of_numbers += std::stoi(number);
			data.replace(0, length_of_number + 2, "");
		}
		else
		{
			this->sum_of_numbers += std::stoi(data);
			data.clear();
		}
	}
}

void BufferHandler::writeData(std::mutex& console_mtx)
{
	std::scoped_lock lock(console_mtx);
	std::cout << "Recieved data is: " << data << std::endl;
}

void BufferHandler::sendData()
{
	Client client;
	client.sendData(sum_of_numbers);
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
			writeData(console_mtx);
		}
		sum();
		sendData();
	}
}