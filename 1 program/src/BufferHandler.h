#include "Interface.h"
#include <chrono>

class BufferHandler : private InterfaceAdder, public InterfaceHandler
{
public:
	void doTask(Buffer& buffer) override;
private:
	void sum() override;

	void readFromBuffer(Buffer& buffer);
	void writeData(std::mutex& console_mtx);
	void sendData();

	std::string data;
	long long int sum_of_numbers = 0;
};
