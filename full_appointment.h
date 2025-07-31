#pragma once
#include "make_appointment.h"
#include "identity.h"


class full_appointment : public make_appointment {
private:
    int32_t user_id = EMPTY;	// ԤԼ�û�ID
    int32_t room_id = EMPTY;	// ����ID
    int32_t status = EMPTY;		// ԤԼ״̬�������1/ͨ��2/�ܾ�3/ȡ��4��
public:
	int32_t return_user_id() const {
		return user_id;
	}
	int32_t return_room_id() const {
		return room_id;
	}
	int32_t return_status() const {
		return status;
	}


	void input_status(const int32_t status) {
		this->status = status;
	}
	void input_user_id(const int32_t user_id) {
		this->user_id = user_id;
	}
	void input_room_id(const int32_t room_id) {
		this->room_id = room_id;
	}
};

