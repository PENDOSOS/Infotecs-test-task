#include "Client.h"

Client::Client()
{
	socketDescriptor = socket(PF_LOCAL, SOCK_STREAM, 0);
	if (socketDescriptor < 0) {
		throw std::runtime_error("Error while open socket");
	}
	params.sa_family = AF_LOCAL;
}

Client::~Client()
{
	if (close(socketDescriptor) < 0) {
		std::cerr << "Error while closing socket\n";
	}
}

void Client::connectToServer()
{
	if (connect(socketDescriptor, &params, sizeof(params)) < 0) {
		throw std::runtime_error("Can't connect to server");
	}
	newSocketDescriptor = socketDescriptor;
}

void Client::sendData(int x) const
{
	send(newSocketDescriptor, &x, sizeof(x), 0);
}