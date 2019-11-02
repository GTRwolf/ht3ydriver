#include "HT3YDRIVER.h"
#include <Windows.h>
#include <thread>
#include <functional>
#include <iostream>

int HT3YDRIVER::init(const char* port, int buadrate, char bits, parity parity, char stopbit) {
	serial_port->open(port, buadrate, parity, bits, stopbit, 1);
	std::thread thread_recv = std::thread(std::mem_fn(&HT3YDRIVER::read_test), this, read_buffer, i);
	thread_recv.detach();
	//thread_join join_thread_recv(thread_recv);
	std::cout << "thread_recv_mavlink ID is: " << thread_recv.get_id() << std::endl; 
	return 0;
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

int HT3YDRIVER::read_test(char * r_buffer, int & i) {
	int read_size = 0;
	i = 0;
	while (true) {
		read_size = serial_port->receive(r_buffer, 1024);
		Sleep(10);
		//std::cout << "read size is: " << read_size << std::endl;
		//std::cout << "read buffer :" << r_buffer << std::endl;
		i++;
	}
	return read_size;
}

int HT3YDRIVER::write_test(char * send_buffer, uint16_t sz) {
	int wCount;
	wCount = serial_port->send(send_buffer, (int)sz);
	std::cout << "send size is: " << wCount << std::endl;
	Sleep(10);
	return wCount;
}


void HT3YDRIVER::multi_thread_test() {
	int i = 0;
	while(true) {
		printf("read buffer size is: %d\n", i);
		Sleep(500);
		i++;
	}
}
