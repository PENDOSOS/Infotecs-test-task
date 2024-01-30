#include <iostream>
#include <thread>
#include <string>
#include "UserStringHandler.h"

int main()
{
	std::string buffer;

	UserStringHandler thr1;

	thr1.doTask(buffer);

	return 0;
}