#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>



template <typename T>
class InterfaceHandler
{
public:
	virtual void doTask(T& buffer, std::mutex& console_mtx, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled) = 0;
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