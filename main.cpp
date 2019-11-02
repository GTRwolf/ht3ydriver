#include <iostream>
#include "WzSerialPort.h"
#include "HT3YDRIVER.h"

using namespace std;

int main(int argumentCount, const char* argumentValues[]) {
	char read_buffer[1024] = {};
	HT3YDRIVER ht3y_driver;
	int a = ht3y_driver.init("COM3", 9600, 8, NO, 1);
	char buf[1024] = "test, write!!!";
	ht3y_driver.write_test(buf, strlen(buf));
	printf("init successful ！！！%d\n", a);
	uint16_t sz;	
	//ht3y_driver.write_test(buf, strlen(buf));
	printf("send a buffer ！！！\n");
	while (true) {
		Sleep(200);
		printf("wait 200ms, %d\n", ht3y_driver.i);
	}
	//int rCount = ht3y_driver.read_test(read_buffer);
	//std::cout << "read buffer is :" << read_buffer << std::endl;
	//std::cout << "read buffer size is :" << rCount << std::endl;
	getchar();
	return 0;
}