#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>

struct Buffer
{
	std::string data;
	std::condition_variable buffer_check;
	std::mutex console_mtx;
	std::mutex buffer_mtx;
	bool is_filled = false;
};

//template <typename T>
class InterfaceHandler
{
public:
	virtual void doTask(Buffer& buffer) = 0;
};

class InterfaceFormatter
{
public:
	virtual void sort() = 0;

	virtual void replceEven() = 0;
};

class InterfaceChecker
{
public:
	virtual bool checkLength() = 0;

	virtual bool checkForDigits() = 0;
};

class InterfaceAdder
{
public:
	virtual void sum() = 0;
};