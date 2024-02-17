#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <exception>

class Client
{
public:
	Client();

	~Client();

	void connectToServer();
	

	void sendData(int x) const;

private:
	int socketDescriptor{};
	sockaddr params{};
	int newSocketDescriptor{};
};

