#include "Interface.h"

class BufferHandler : private InterfaceAdder, public InterfaceHandler<std::string>
{
public:
	void doTask(std::string& buffer) override;
private:
	void sum() override;

	void readFromBuffer(std::string& buffer);
	void writeData();
	void sendData();

	std::string data;
	int sum_of_numbers = 0;
};