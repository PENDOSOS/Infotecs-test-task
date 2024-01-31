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