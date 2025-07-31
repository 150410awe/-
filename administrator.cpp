#include "administrator.h"
#include <iostream>
#include "data_management.h"
#include <fstream>

using namespace std;

//identity* data_management::current_user;

void administrator::add() {
	string s_id;
	double id = EMPTY;
	string name;
	string password;
	string choice;
	
	cout << "请输入id" << endl;
	cin >> s_id;
	cout << "请输入密码" << endl;
	cin >> password;
	cout << "请输入名字" << endl;
	cin >> name;

	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	cin >> choice;

	if (management.pure_num(s_id))
		if (management.beyond_scope(id) == true)
			id = stoi(s_id);
		else {
			cout << "id文字太长" << endl;
			return;
		}
	else {
		cout << "id不为纯数字" << endl;
		return;
	}



	if (choice == "1") {
		student data;
		data.input_id(id);
		data.input_name(name);
		data.input_password(password);
		if (management.duplicate_id(data, management.students) == true) {
			cout << "id重复,添加失败" << endl;
			return;
		}
		cout << "添加成功" << endl;
		management.students.insert({ data.return_id(), data });
		management.save_account(data, project_paths::STUDENT_FILE);
	}
	else if (choice == "2") {
		teacher data;
		data.input_id(id);
		data.input_name(name);
		data.input_password(password);
		if (management.duplicate_id(data, management.teachers) == true) {
			cout << "id重复,添加失败" << endl;
			return;
		}
		cout << "添加成功" << endl;
		management.teachers.insert({ data.return_id(), data });
		management.save_account(data, project_paths::TEACHER_FILE);
	}
	else {
		cout << "身份输入错误" << endl;
		return;
	}
}

void administrator::view_account() const {
	cout << "学生" << endl;
	for (auto it = management.students.begin(); it != management.students.end(); it++)
		cout << "id: " << (*it).second.return_id() << "\t密码: " << (*it).second.return_password() << "\t名字: " << (*it).second.return_name() << endl;
	cout << "老师" << endl;
	for (auto it = management.teachers.begin(); it != management.teachers.end(); it++)
		cout << "id: " << (*it).second.return_id() << "\t密码: " << (*it).second.return_password() << "\t名字: " << (*it).second.return_name() << endl;
}

//void administrator::check_computer_room() const {
//	cout << "机房信息" << endl;
//	for (auto it = management.room.begin(); it != management.room.end(); it++)
//		cout << "机房id: " << (*it).second.return_id() << "\t可用机位: " << (*it).second.return_available() << "\t最大容量: " << (*it).second.return_capacity() << "\t名字: " << (*it).second.return_name() << endl;
//}

void administrator::clear() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	string temp;

	cin >> temp;

	if (temp != "1") {
		cout << "已取消清空操作" << endl;
		return;
	}

	cout << "确认" << endl;
	ofstream print(project_paths::ORDER_FILE, ios::trunc);
	print.close();

	management.appointments.clear();

	cout << "清空成功" << endl;
}

void administrator::erase() {
	string day;
	string period;
	string room_id;
	string status;
	string user_id;

	management.view_all_appointments();

	cout << "请输入天:" << endl;
	cin >> day;
	cout << "请输入周期" << endl;
	cin >> period;
	cout << "请输入学生ID" << endl;
	cin >> user_id;
	cout << "请输入机房ID" << endl;
	cin >> room_id;
	cout << "请输入预约状态" << endl;
	cout << "审核1/通过2/拒绝3/取消4" << endl;
	cin >> status;

	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	if (management.duplicate_key(key) == false) {
		cout << "没有这个预约" << endl;
		return;
	}

	management.appointments.erase(key);
	cout << "删除完成" << endl;
}

//void administrator::view_all_appointments() const {
//
//}

//void administrator::logout() {
//
//}

void administrator::menu() const {
	cout << "1,添加账号" << endl
		<< "2,查看账号" << endl
		<< "3,查看机房" << endl
		<< "4,清空预约" << endl
		<< "5,查看所有预约" << endl
		<< "6,删除预约" << endl
		<< "7,增加机房" << endl
		<< "8,查看所有机房" << endl
		<< "0,退出登录" << endl;
}

//void administrator::login() const {
//
//}

void administrator::input_function() {
	cout << "欢迎管理员:" << data_management::current_user->return_name() << "登陆" << endl;
	menu();
	string choice;
	while (cin >> choice) {
		if (choice == "1")
			add();
		if (choice == "2")
			view_account();
		if (choice == "3")
			management.view_all_room();
		if (choice == "4")
			clear();
		if (choice == "5")
			management.view_all_appointments();	//view_all_appointments();
		if (choice == "6")
			erase();
		if (choice == "7")
			add_computer_room();
		if (choice == "8")
			management.view_all_room();
		if (choice == "0")
			break;
		menu();
	}
}

void administrator::add_computer_room() {
	management.view_all_room();
	string id;
	string name;
	string capacity;
	string available;


	cout << "请输入机房编号:" << endl;
	cin >> id;
	cout << "请输入机房名称" << endl;
	cin >> name;
	cout << "请输入最大机位容量" << endl;
	cin >> capacity;

	computer_room data;

	available = capacity;
	string str = id + '|' + capacity + '|' + available + '|' + name;
	if (management.parsing_room(str, data) == false) {
		cout << "机房输入错误" << endl;
		return;
	}
	if (management.duplicate_id(data, management.room) == true) {
		cout << "id重复,添加失败" << endl;
		return;
	}
	if (management.room_audit(data) == false) {
		cout << "机房数据不合理" << endl;
		return;
	}

	management.room_audit(data);

	management.room.insert({ data.return_id(),data });
	management.save_room(data, project_paths::ROOM_FILE);
	cout << "添加成功" << endl;
}

administrator::administrator() {

}

administrator::~administrator() {

}