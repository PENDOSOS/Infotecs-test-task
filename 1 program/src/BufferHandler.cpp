#include "BufferHandler.h"
#include "Client.h"

void BufferHandler::readFromBuffer(Buffer& buffer)
{
	this->data = std::move(buffer.data);
	buffer.is_filled = false;
}

void BufferHandler::sum()
{
	long long int length_of_number = 0;
	std::string number;
	while (data.length() != 0)
	{
		length_of_number = data.find("KB");
		if (length_of_number != std::string::npos)
		{
			number = data.substr(0, length_of_number);
			if (number.length() != 0)
				this->sum_of_numbers += std::stoll(number);
			data.replace(0, length_of_number + 2, "");
		}
		else
		{
			this->sum_of_numbers += std::stoll(data);
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
	client.connectToServer();
	client.sendData(sum_of_numbers);
	sum_of_numbers = 0;
}

void BufferHandler::doTask(Buffer& buffer)
{
	while (true)
	{
		{
			std::unique_lock<std::mutex> locker(buffer.buffer_mtx);
			buffer.buffer_check.wait(locker, [&buffer] { return buffer.is_filled; });
			readFromBuffer(buffer);
			writeData(buffer.console_mtx);
		}
		sum();
		try
		{
			sendData();
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl;
		}
	}
}
