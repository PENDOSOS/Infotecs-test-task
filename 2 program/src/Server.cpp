#include "Server.h"

Server::Server()
{
	socket_descriptor = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socket_descriptor < 0)
	{
		throw std::runtime_error("Error while open socket");
	}
	params.sa_family = AF_UNIX;
}

Server::~Server()
{
	if (close(socket_descriptor) < 0)
	{
		std::cerr << "Error while closing socket\n";
	}
}

void Server::setOnlineStatus()
{
	if (bind(socket_descriptor, &params, sizeof(params)) < 0)
	{
		//throw std::runtime_error("Error while bind socket");
	}
	if (listen(socket_descriptor, 1) < 0)
	{
		//throw std::runtime_error("Error while listen socket");
	}
	int len = sizeof(params);
	if ((new_socket_descriptor = accept(socket_descriptor, &params, (socklen_t*)&len)) < 0)
	{
		//throw std::runtime_error("Error while accept client");
	}
	//std::cout << "Server online" << std::endl;
}

std::optional<int> Server::getInt() const
{
	int x{};
	int success = read(new_socket_descriptor, &x, sizeof(x));
	if (success < 0)
	{
		throw std::runtime_error("Error while read from socket");
	}
	if (success == 0)
	{
		return std::nullopt;
	}
	return x;
}
