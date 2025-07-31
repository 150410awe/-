#pragma once
#include "make_appointment.h"
#include "identity.h"


class full_appointment : public make_appointment {
private:
    int32_t user_id = EMPTY;	// 预约用户ID
    int32_t room_id = EMPTY;	// 机房ID
    int32_t status = EMPTY;		// 预约状态（待审核1/通过2/拒绝3/取消4）
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

