#pragma once
#include <filesystem>
#include <fstream>
#include <string>


namespace project_paths {
	const std::string STUDENT_FILE = "student.txt";
	const std::string TEACHER_FILE = "teacher.txt";
	const std::string ADMIN_FILE = "administrator.txt";
	const std::string ROOM_FILE = "computer_room.txt";
	const std::string ORDER_FILE = "make_appointment.txt";

	// ����ļ��Ƿ����
	inline bool empty(const std::string path) {
		std::ifstream file(path);
		return file.good();  // �ļ������ҿɶ�ʱ����true
	}
}


