#include <iostream>
#include <string>
#include "UserStringHandler.h"
#include "BufferHandler.h"

void task(InterfaceHandler<std::string>& interface, std::string& buffer, std::mutex& console_mtx, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled)
{
	interface.doTask(buffer, console_mtx, buffer_mtx, buffer_check, is_filled);
}

int main()
{
	std::string buffer;

	std::condition_variable buffer_check;
	std::mutex console_mtx;
	std::mutex buffer_mtx;
	bool is_filled = false;

	UserStringHandler thr1;
	BufferHandler thr2;

	std::thread thread_1(task, std::ref(thr1), std::ref(buffer), std::ref(console_mtx), std::ref(buffer_mtx), std::ref(buffer_check), std::ref(is_filled));
	std::thread thread_2(task, std::ref(thr2), std::ref(buffer), std::ref(console_mtx), std::ref(buffer_mtx), std::ref(buffer_check), std::ref(is_filled));

	//thr1.doTask(buffer);
	//thr2.doTask(buffer);

	thread_1.join();
	thread_2.join();

	return 0;
}