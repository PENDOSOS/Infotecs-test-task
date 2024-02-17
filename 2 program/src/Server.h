#pragma once

#include <iostream>
#include <optional>
#include <exception>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Server
{
public:
	Server();

	~Server();

	void setOnlineStatus();

	std::optional<int> getInt() const;

private:
	int socket_descriptor {};
	sockaddr params {};
	int new_socket_descriptor {};
};

