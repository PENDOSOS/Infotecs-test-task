#pragma once
#include "Interface.h"

class UserStringHandler : private InterfaceFormatter, private InterfaceChecker, public InterfaceHandler<std::string>
{
public:
	void doTask(std::string& buffer, std::mutex& console_mtx, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled) override;

private:
	void sort() override;
	void replceEven() override;

	bool checkLength() override;
	bool checkForDigits() override;

	void writeIntoBuffer(std::string& buffer, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled);

	std::string data;
};

