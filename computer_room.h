#pragma once
#include <string>
#include <cstdint>
#include "identity.h"

class computer_room {
private:
	int32_t id = EMPTY;		// 机房编号
	std::string name;	// 机房名称
	int32_t capacity = 0;// 最大容量
	int32_t available = 0;// 可用机位
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