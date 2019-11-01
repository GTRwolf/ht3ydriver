
#include <iostream>
#include "WzSerialPort.h"
#include "HT3YDRIVER.h"

using namespace std;

int main(int argumentCount, const char* argumentValues[]) {
	HT3YDRIVER ht3y_driver;
	ht3y_driver.init("COM3", 9600, 8, NO, 1);
	printf("init successful ！！！\n");
	uint16_t sz;
	char buf[1024] = "test, write!!!";
	char read_buffer[1024] = {};
	ht3y_driver.write(buf, strlen(buf));
	//int rCount = ht3y_driver.read_test(read_buffer);
	//std::cout << "read buffer is :" << read_buffer << std::endl;
	//std::cout << "read buffer size is :" << rCount << std::endl;

	return 0;
}