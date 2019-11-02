#pragma once
#include "serial.h"
#include "WzSerialPort.h"
#include <vector>
#include <string>
#include <thread>
struct st_status
{
	//TODO
};

class HT3YDRIVER
{
public:
	HT3YDRIVER() {}
	~HT3YDRIVER() {}
	int init(const char* port, int buadrate, char bits, parity parity, char stopbit);
	int read(std::vector<st_status>& vt_status, char* buffer2send, uint16_t & sz);
	int write(char* buffer2write, uint16_t sz);

	//测试用代码
	int read_test(char * read_buffer, int & i);
	int write_test(char * send_buffer, uint16_t sz);
	void multi_thread_test();
	int  i;

	//单例实例化串口类
	WzSerialPort* serial_port = WzSerialPort::getInstance();

private:
	void thread_recv_data(std::vector<st_status> & vt_status, char * buffer2send, uint16_t & sz);
	std::vector<st_status> vt_status;
	std::string buffer2send;
	char read_buffer[1024];
	
};

class thread_join {
private:
	std::thread& m_t;

public:
	explicit thread_join(std::thread& t) :m_t(t) {}
	~thread_join() {
		if (m_t.joinable()) {
			m_t.join();
		}
	}
};