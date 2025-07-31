#include "student.h"
#include "data_management.h"
#include <iostream>

using namespace std;

//identity* data_management::current_user;

void student::application() {

	string day;
	string period;
	string room_id;
	string user_id = to_string(data_management::current_user->return_id());
	string status = "1";//默认待审核

	management.view_all_appointments();

	cout << "请输入天:" << endl;
	cin >> day;
	cout << "请输入周期" << endl;
	cin >> period;
	cout << "请输入机房ID" << endl;
	cin >> room_id;


	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	if (management.duplicate_key(key) == true) {
		cout << "有这个预约,申请失败" << endl;
		return;
	}

	full_appointment data;

	if (management.analysis_reservation(key, data) == false) {
		cout << "预约输入错误" << endl;
		return;
	}
	if (management.room_existence(stoi(room_id)) == false) {
		cout << "机房输入错误" << endl;
		return;
	}
	if (management.review_appointment_data(data) == false) {
		cout << "预约数据不合理" << endl;
		return;
	}

	management.appointments.insert({ key, data });
	management.save_reservation(data, project_paths::ORDER_FILE);
	cout << "申请成功" << endl;
}

void student::look_yourself() const {
	int32_t id = management.current_user->return_id();

	cout << "我的预约" << endl;

	for (auto it = management.appointments.begin(); it != management.appointments.end(); it++)
		if ((*it).second.return_user_id() == id)
			cout << "天: " << (*it).second.return_day()
			<< "\t周期: " << (*it).second.return_periody()
			<< "\t预约用户ID： " << (*it).second.return_user_id()
			<< "\t机房ID: " << (*it).second.return_room_id()
			<< "\t预约状态: " << (*it).second.return_status() << endl;
}

//void student::view_all_appointments() const {
//
//}

void student::cancel() {
	cout << "请输入预约信息" << endl;

	string day;
	string period;
	string room_id;
	string user_id = to_string(data_management::current_user->return_id());
	string status;

	look_yourself();

	cout << "请输入天:" << endl;
	cin >> day;
	cout << "请输入周期" << endl;
	cin >> period;
	cout << "请输入机房ID" << endl;
	cin >> room_id;
	cout << "请输入预约状态待审核1/通过2" << endl;	
	cin >> status;
	if (status != "1" && status != "2") {
		cout << "预约状态错误" << endl;
		return;
	}

	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	full_appointment data;

	if (management.duplicate_key(key) == false) {
		cout << "没有这个预约,取消失败" << endl;
		return;
	}
	//add和加载时保证了key是正确的所以不用防御性编程了;
	management.appointments.erase(key);
	//在写一个太麻烦了,用save_reservation,主要是我不会;
	status = "4";
	key = management.generate_appointment_key(day, period, user_id, room_id, status);//为了防止出现神秘问题,所以重新赋值
	management.analysis_reservation(key, data);
	management.appointments.insert({ key, data });
	management.save_reservation(data, project_paths::ORDER_FILE);
	cout << "取消成功" << endl;
}

//void student::logout() {
//
//}

void student::menu() const {
	cout << "1,申请预约" << endl
		<< "2,查看我的预约" << endl
		<< "3,查看所有预约" << endl
		<< "4,取消预约" << endl
		<< "5,查看所有机房" << endl
		<< "0,退出登录" << endl;
}

//void student::login() const{
//
//}

void student::input_function() {
	cout << "欢迎学生:" << data_management::current_user->return_name() << "登陆" << endl;
	string choice;
	menu();
	while (cin >> choice) {
		if (choice == "1")
			application();
		if (choice == "2")
			look_yourself();
		if (choice == "3")
			management.view_all_appointments();			//view_all_appointments();
		if (choice == "4")
			cancel();
		if (choice == "5")
			management.view_all_room();
		if (choice == "0")
			break;
			
		menu();
	}
}


student::student() {

}

student::~student() {

}