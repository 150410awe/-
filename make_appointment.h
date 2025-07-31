#pragma once
#include <cstdint>
#include "identity.h"

class make_appointment {
private:
	int32_t day = EMPTY;
	int32_t period = EMPTY;
public:
	int32_t return_day() const {
		return day;
	}
	int32_t return_periody() const {
		return period;
	}

	void input_period(const int32_t period) {
		this->period = period;
	}
	void input_day(const int32_t day) {
		this->day = day;
	}
};