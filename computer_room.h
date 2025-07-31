#pragma once
#include <string>
#include <cstdint>
#include "identity.h"

class computer_room {
private:
	int32_t id = EMPTY;		// �������
	std::string name;	// ��������
	int32_t capacity = 0;// �������
	int32_t available = 0;// ���û�λ
public:

	int32_t return_id() const {
		return id;
	}
	const std::string& return_name() const {
		return name;
	}
	int32_t return_capacity() const {
		return capacity;
	}
	int32_t return_available() const {
		return available;
	}

	void input_id(int32_t id) {
		this->id = id;
	}
	void input_name(const std::string name) {
		this->name = name;
	}
	void input_capacity(const int32_t capacity) {
		this->capacity = capacity;
	}
	void input_available(const int32_t available) {
		this->available = available;
	}
};