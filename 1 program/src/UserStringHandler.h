#pragma once
#include "Interface.h"

class UserStringHandler : private InterfaceFormatter, private InterfaceChecker, public InterfaceHandler
{
public:
	void doTask(Buffer& buffer) override;

private:
	void sort() override;
	void replceEven() override;

	bool checkLength() override;
	bool checkForDigits() override;

	void writeIntoBuffer(Buffer& buffer);

	std::string data;
};

