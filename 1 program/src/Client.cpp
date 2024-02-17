#include "Client.h"

Client::Client()
{
	socketDescriptor = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socketDescriptor < 0) {
		throw std::runtime_error("Error while open socket");
	}
	params.sa_family = AF_UNIX;
}

Client::~Client()
{
	if (close(socketDescriptor) < 0) {
		std::cerr << "Error while closing socket\n";
	}
}

void Client::connectToServer()
{
	if (connect(socketDescriptor, &params, sizeof(params)) >= 0) {
		newSocketDescriptor = socketDescriptor;
	}
}

void Client::sendData(int x) const
{
	send(newSocketDescriptor, &x, sizeof(x), 0);
}
