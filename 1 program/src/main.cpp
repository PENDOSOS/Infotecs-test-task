#include <iostream>
#include <string>
#include "UserStringHandler.h"
#include "BufferHandler.h"

void task(InterfaceHandler& interface, Buffer& buffer)
{
	interface.doTask(buffer);
}

int main()
{
	Buffer buffer;	

	UserStringHandler thr1;
	BufferHandler thr2;

	std::thread thread_1(task, std::ref(thr1), std::ref(buffer));
	std::thread thread_2(task, std::ref(thr2), std::ref(buffer));

	thread_1.join();
	thread_2.join();

	return 0;
}
