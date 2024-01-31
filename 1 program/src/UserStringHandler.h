#pragma once
#include "Interface.h"

class UserStringHandler : private InterfaceFormatter, private InterfaceChecker, public InterfaceHandler<std::string>
{
public:
	void doTask(std::string& buffer) override;

private:
	void sort() override;
	void replceEven() override;

	bool checkLength() override;
	bool checkForDigits() override;

	void writeIntoBuffer(std::string& buffer);

	std::string data;
};

