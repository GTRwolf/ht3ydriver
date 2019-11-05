#include <iostream>
#include "WzSerialPort.h"
#include "HT3YDRIVER.h"
#include <Windows.h>

using namespace std;

int main(int argc, const char* arv[]) {
	char read_buffer[1024] = {};
	std::vector<mavlink_px4tonuc_t> vt_mavlink_px4tonuc;
	std::vector<mavlink_attitude_t> vt_attitude;
	//mavlink_message_t msg;
	//mavlink_status_t msg_status;
	HT3YDRIVER ht3y_driver;
	uint16_t size = 0;
	uint64_t thread_id = ht3y_driver.init("COM3",57600, 8, NO, 1);
	char buf[20] = "test, write";
	ht3y_driver.read(vt_attitude, read_buffer, size);
	//std::cout << "main thread : vt_attitude size is" << vt_attitude.size() << std::endl;
	for (int i = 0; i < 20; i++) {
		ht3y_driver.write(buf, strlen(buf));
		ht3y_driver.read(vt_attitude, read_buffer, size);
		//std::cout << "main thread : vt_attitude size is" << vt_attitude.size() << std::endl;
		Sleep(10);
	}
	return 0;
}