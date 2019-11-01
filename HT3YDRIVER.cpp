#include "HT3YDRIVER.h"
#include <Windows.h>

int HT3YDRIVER::init(const char* port, int buadrate, char bits, parity parity, char stopbit) {
	serial_port->open(port, buadrate, parity, bits, stopbit, 1);
	Serial_Receive_init();
	printf("init successful!!!\n");
	return 1;
}

int HT3YDRIVER::read(std::vector<st_status>& vt_status, char* buffer2send, uint16_t & sz) {
	int read_sz = 0;
	return read_sz;
}

int HT3YDRIVER::write(char* buffer2write, uint16_t sz) {
	int write_sz = serial_port->send(buffer2write, (int)sz);
	if (write_sz) {
		return write_sz;
	}
	else {
		return -1;
	}
}

int HT3YDRIVER::read_test(char * read_buffer) {
	int read_size = 0;
	read_size = serial_port->receive(read_buffer, 1024);
	return read_size;
}

int HT3YDRIVER::write_test(char * send_buffer, uint16_t sz) {
	int wCount;
	wCount = serial_port->send(send_buffer, (int)sz);
	return wCount;
}

DWORD WINAPI HT3YDRIVER::Thread_Receive(LPVOID pParam) {
	//HT3YDRIVER * pFun = (HT3YDRIVER *)pParam;
	char read_buffer[1024] = {};
	int read_buffer_size = 0;
	//uint16_t size;
	int i = 0;
	while (true) {
		printf("thread receive is running\n");
		//read_buffer_size = pFun->read_test(read_buffer);
		//if (read_buffer_size <= 0) {
		//	continue;
		//}

		printf("read buffer size is: %d\n", i);
		i++;
	}
}

void HT3YDRIVER::Serial_Receive_init() {
	HANDLE hThread; //线程句柄
	DWORD threadID; //线程ID
	hThread = CreateThread(NULL, 0, Thread_Receive, this, 0, &threadID);
	printf("thread id is : %d\n", threadID);
}