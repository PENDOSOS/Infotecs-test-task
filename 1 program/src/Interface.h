#pragma once

#include <iostream>
#include <string>

template <typename T>
class InterfaceHandler
{
public:
	virtual void doTask(T& buffer) = 0;
};

class InterfaceFormatter
{
public:
	virtual void sort() = 0;

	virtual void repalceEven() = 0;
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
	virtual bool sum() = 0;
};