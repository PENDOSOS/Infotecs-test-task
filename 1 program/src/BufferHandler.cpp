#include "BufferHandler.h"

void BufferHandler::readFromBuffer(std::string& buffer)
{
	this->data = std::move(buffer);
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
			i++;
		}
		else if (data[i] == 'K' || i == data.length() - 1)
		{
			length_of_number = i - begin_of_number;
			number = data.substr(begin_of_number, length_of_number);
			this->sum_of_numbers += std::stoi(number);
		}
	}
}

void BufferHandler::writeData()
{
	std::cout << "Recieved data is: " << data << std::endl;
}

void BufferHandler::sendData()
{

}

void BufferHandler::doTask(std::string& buffer)
{
	readFromBuffer(buffer);
	writeData();
	sum();
	sendData();
}