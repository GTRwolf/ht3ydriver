#pragma once
#include "WzSerialPort.h"
#include "mavlink/v2.0/standard/mavlink.h"
#include "mavlink/v2.0/mavlink_helpers.h"
#include <vector>
#include <string>
#include <thread>

#define MAX_READ_BYTES 1024

//��Ժ״̬֡
//#pragma pack (1)
//struct st_status
//{
//	uint16_t frame_head = 0x55AA;
//	uint16_t frame_seq = 0xAB81;
//	uint16_t frame_count;
//	uint16_t uav_status;
//	uint8_t  commond_finished; //ָ����ɱ�ʶ��
//	uint8_t  waypoint_uploaded;
//	int32_t  position_north;
//	int32_t  position_east;
//	int32_t  altitude; //����λ��
//	int32_t  northern_velocity;
//	int32_t  eastern_velocity;
//	int32_t  vetical_velocity; //�����ٶ�
//	int16_t  picth_angle;
//	int16_t  roll_angle;
//	int16_t  yaw_angle;
//	int32_t  longitude;
//	int32_t  latitude;
//	int64_t  UTC_time;
//	uint8_t  GPS_satellites_amount;
//	uint8_t  GPS_mode;
//	uint8_t  self_check_finished;
//	uint16_t self_check_status;
//	int32_t  PTZ_pitch_angle; //��̨������ܽ�
//	uint8_t  cast_status; //Ͷ��״̬
//	uint8_t  mission_finished; //������ɱ�ʶ
//	uint8_t  control_mode;
//	int32_t  barometric_altitude; //��ѹ��
//	int32_t  radar_altitude; //�״��
//	int32_t  acceleration_altitude; //���ٶȸ�
//	int32_t  satellite_altitude; //���Ǹ�
//	int16_t  acceleration_x;
//	int16_t  acceleration_y;
//	int16_t  acceleration_z;
//	int16_t  angular_velocity_x;
//	int16_t  angular_velocity_y;
//	int16_t  angular_velocity_z;
//	int16_t  airspeed;
//	uint8_t  reserve[8]; //Ԥ����8���ֽ�
//	uint16_t  checksum;
//};

enum parity
{
	NO = 0,
	ODD = 1,
	EVEN = 2
};

class mythread {
private:
	std::thread& m_t;

public:
	explicit mythread(std::thread& t) :m_t(t) {}
	~mythread() {
		if (m_t.joinable()) {
			m_t.join();
		}
	}
};

class HT3YDRIVER
{
public:

	//��ʼ������
	int init(const char* port, int buadrate, char bits, parity parity, char stopbit);

	//������,�Ǵ��ڶ�����
	int read(std::vector<mavlink_px4tonuc_t>& vt_uav_status, char* buffer2send, uint16_t & sz);

	//����д����
	int write(char* buffer2write, uint16_t sz);

	//�����ô���
	//int read_test(char * read_buffer, int & i);
	//int write_test(char * send_buffer, uint16_t sz);
	//int  i;
	int read(std::vector<mavlink_attitude_t>& vt_attitude_, char* buffer2send, uint16_t& sz);

	

private:
	//�����̵߳��̺߳���
	void thread_recv_data();

	//��ȡ�߳�id
	uint64_t get_thread_id(std::thread & thread_check);

	//�����ڶ�ȡ�����ݽ���Ϊmavlink��
	void data_parse_to_mavlink(char* buffer, int sz, mavlink_message_t& msg, mavlink_status_t& status);

	//����ʵ����������
	WzSerialPort* serial_port = WzSerialPort::getInstance();

	std::vector<mavlink_px4tonuc_t> vt_px4tonuc;
	char buffer2send_[MAX_READ_BYTES] = {};
	bool px4tonuc_update = false;
	mavlink_px4tonuc_t px4tonuc;

	//������
	mavlink_heartbeat_t heartbeat;
	mavlink_attitude_t attitude_t;
	std::vector<mavlink_attitude_t> vt_attitude;
	std::vector<mavlink_heartbeat_t> vt_heartbeat;
	bool attitude_update = false;
	bool heartbeat_update = false;
};