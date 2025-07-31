#include "teacher.h"
#include "data_management.h"
#include <iostream>

//identity* data_management::current_user;

using namespace std;

void teacher::audit() {
	management.view_all_appointments();

	string day;
	string period;
	string room_id;
	string user_id;
	string status = "1";//待审核

	cout << "请输入天:" << endl;
	cin >> day;
	cout << "请输入周期" << endl;
	cin >> period;
	cout << "请输入学生id" << endl;
	cin >> user_id;
	cout << "请输入机房ID" << endl;
	cin >> room_id;


	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	full_appointment data;
	cout << key << endl;
	if (management.duplicate_key(key) == false) {
		cout << "没有这个预约,审核失败" << endl;
		return;
	}

	cout << "通过2 or 拒绝3" << endl;
	string choice;
	cin >> choice;
	if (choice != "2" && choice != "3") {
		cout << "选择错误" << endl;
		return;
	}

	management.appointments.erase(key);

	status = choice;

	key = management.generate_appointment_key(day, period, user_id, room_id, status);
	management.analysis_reservation(key, data);
	management.appointments.insert({ key, data });
	management.save_reservation(data, project_paths::ORDER_FILE);
	cout << "审核成功" << endl;
}

//void teacher::view_all_appointments() const {
//
//}

//void teacher::logout() {
//
//}

void teacher::menu() const {
	cout << "1,审核预约" << endl
		<< "2,查看所有预约" << endl
		<< "3,查看所有机房" << endl
		<< "0,退出登录" << endl;
}

//void teacher::login() const {
//
//}


void teacher::input_function() {
	cout << "欢迎学生:" << data_management::current_user->return_name() << "登陆" << endl;
	string choice;
	menu();
	while (cin >> choice) {
		if (choice == "1")
			audit();
		if (choice == "2")
			management.view_all_appointments();
		if (choice == "3")
			management.view_all_appointments();
		if (choice == "0")
			break;

		menu();
	}
}

teacher::teacher() {

}

teacher::~teacher() {

}