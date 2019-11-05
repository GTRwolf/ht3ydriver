#include "HT3YDRIVER.h"
#include <stdio.h>
#include <Windows.h>
#include <functional>
#include <iostream>
#include <sstream>

int HT3YDRIVER::init(const char* port, int buadrate, char bits, parity parity, char stopbit) {
	bool open_uart_successful = false;
	open_uart_successful = serial_port->open(port, buadrate, parity, bits, stopbit, 1);
	if (!open_uart_successful) {
		std::cout << "Open UART Failed!!!" << std::endl;
		exit(-1);
	}
	std::thread thread_recv = std::thread(std::mem_fn(&HT3YDRIVER::thread_recv_data), this);
	thread_recv.detach();
	return 1;
}

int HT3YDRIVER::read(std::vector<mavlink_px4tonuc_t>& vt_uav_status, char* buffer2send, uint16_t & sz) {
	vt_uav_status = vt_px4tonuc;
	sz = strlen(buffer2send_);
	memcpy(buffer2send, buffer2send_, sz);
	return 1;
}

int HT3YDRIVER::write(char* buffer2write, uint16_t sz) {
	int write_sz = serial_port->send(buffer2write, sz);
	if (write_sz) {
		return write_sz;
	}
	else {
		return -1;
	}
}

uint64_t HT3YDRIVER::get_thread_id(std::thread & thread_check) {
	std::thread::id id = thread_check.get_id();
	std::stringstream sin;
	sin << id;
	return std::stoull(sin.str());
}

void HT3YDRIVER::thread_recv_data() {
	std::cout << "start receive data thread !!!" << std::endl;
	int read_data_size = 0;
	mavlink_message_t msg;
	mavlink_status_t mav_status;
	char recv_buffer[MAX_READ_BYTES];
	while (true) {
		read_data_size = serial_port->receive(recv_buffer, MAX_READ_BYTES);
		if (read_data_size < 0 ) {
			std::cout << "no data" << std::endl;
			Sleep(10);
			continue;
		}
		std::cout << "recv_size is :" << read_data_size << ", recv_buffer is : " << recv_buffer << std::endl;
		std::cout << "size: " << strlen(recv_buffer) << std::endl;
		data_parse_to_mavlink(recv_buffer, read_data_size, msg, mav_status);
		
		//更新状态帧的vector
		if (px4tonuc_update) {
			vt_px4tonuc.insert(vt_px4tonuc.end(), px4tonuc);
		}
		Sleep(10);
	}
}

void HT3YDRIVER::data_parse_to_mavlink(char* buffer, int sz, mavlink_message_t& msg, mavlink_status_t& status) {
	int j = 0;
	for (int i = 0; i < sz; i++) {
		if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &status)) {
			switch (msg.msgid) {
			case MAVLINK_MSG_ID_HEARTBEAT:
				//std::cout << "heartbeat" << msg.msgid << std::endl;
				mavlink_msg_heartbeat_decode(&msg, &heartbeat);
				heartbeat_update = true;
				break;
			case MAVLINK_MSG_ID_ATTITUDE:
				//std::cout << "attitude" << msg.msgid << std::endl;
				mavlink_msg_attitude_decode(&msg, &attitude_t);
				attitude_update = true;
				break;
			case MAVLINK_MSG_ID_HIL_STATE:
				//std::cout <<" HIL STATE" << msg.msgid << std::endl;
				break;
			//default:
				
			//	buffer2send_[j] = buffer[i];
			//	j++;
			//	break;
			}
			/*if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
				std::cout << msg.msgid << std::endl;
				mavlink_msg_heartbeat_decode(&msg, &heartbeat);
				px4tonuc_update = true;
			} else {
				buffer2send_[j] = buffer[i];
				j++;
			}*/
		}
		if (attitude_update) {
			vt_attitude.insert(vt_attitude.end(), attitude_t);
			//std::cout << "vt_attitude size" << vt_attitude.size() << std::endl;
			attitude_update = false;
		}
		if (heartbeat_update) {
			vt_heartbeat.insert(vt_heartbeat.end(), heartbeat);
			//std::cout << "vt_heartbeat size" << vt_heartbeat.size() << std::endl;
			heartbeat_update = false;
		}
	}
}

//测试用代码
int HT3YDRIVER::read(std::vector<mavlink_attitude_t>& vt_attitude_t, char* buffer2send, uint16_t& sz) {
	vt_attitude_t = vt_attitude;
	sz = strlen(buffer2send_);
	memcpy(buffer2send, buffer2send_, sz);
	return 1;
}

//int HT3YDRIVER::read_test(char * r_buffer, int & i) {
//	int read_size = 0;
//	i = 0;
//	while (true) {
//		read_size = serial_port->receive(r_buffer, MAX_READ_BYTES);
//		Sleep(10);
//		//std::cout << "read size is: " << read_size << std::endl;
//		std::cout << "read buffer :" << r_buffer << std::endl;
//		i++;
//	}
//	return read_size;
//}
//
//int HT3YDRIVER::write_test(char * send_buffer, uint16_t sz) {
//	int wCount;
//	wCount = serial_port->send(send_buffer, (int)sz);
//	std::cout << "send size is: " << wCount << std::endl;
//	Sleep(10);
//	return wCount;
//}
