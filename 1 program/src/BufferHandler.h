#include "Interface.h"
#include <chrono>

class BufferHandler : private InterfaceAdder, public InterfaceHandler<std::string>
{
public:
	void doTask(std::string& buffer, std::mutex& console_mtx, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled) override;
private:
	void sum() override;

	void readFromBuffer(std::string& buffer, std::mutex& buffer_mtx, std::condition_variable& buffer_check, bool& is_filled);
	void writeData(std::mutex& console_mtx);
	void sendData();

	std::string data;
	int sum_of_numbers = 0;
};