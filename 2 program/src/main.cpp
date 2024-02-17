#include <iostream>
#include "Server.h"
#include <string>

int main()
{
	Server server;
	while (true)
	{
		try
		{
			server.setOnlineStatus();
			auto entry_data = server.getInt();
			if (entry_data.has_value())
			{
				long long int sum = entry_data.value();
				if (sum > 99 && sum % 32 == 0)
					std::cout << "Recieved data is: " << sum << std::endl;
				else
					std::cout << "Error" << std::endl;
			}
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl;
		}
	}

	return 0;
}
