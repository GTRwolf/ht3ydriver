#pragma once
#include "serial.h"
#include "WzSerialPort.h"
#include <vector>
#include <string>
struct st_status
{
	//TODO
};
class HT3YDRIVER
{
public:
	int init(const char* port, int buadrate, char bits, parity parity, char stopbit);
	int read(std::vector<st_status>& vt_status, char* buffer2send, uint16_t & sz);
	int write(char* buffer2write, uint16_t sz);

	//测试用代码
	int read_test(char * read_buffer);
	int write_test(char * send_buffer, uint16_t sz);

	//单例实例化串口类
	WzSerialPort* serial_port = WzSerialPort::getInstance();

public:
	static DWORD WINAPI Thread_Receive(LPVOID pParam);
	void Serial_Receive_init();

private:
	std::vector<st_status> vt_status;
	std::string buffer2send;
};

