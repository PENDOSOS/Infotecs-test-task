#include <iostream>
#include <thread>
#include <string>
#include "UserStringHandler.h"
#include "BufferHandler.h"

int main()
{
	std::string buffer;

	UserStringHandler thr1;
	BufferHandler thr2;

	thr1.doTask(buffer);
	thr2.doTask(buffer);

	return 0;
}