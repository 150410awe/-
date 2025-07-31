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
	
	cout << "������id" << endl;
	cin >> s_id;
	cout << "����������" << endl;
	cin >> password;
	cout << "����������" << endl;
	cin >> name;

	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	cin >> choice;

	if (management.pure_num(s_id))
		if (management.beyond_scope(id) == true)
			id = stoi(s_id);
		else {
			cout << "id����̫��" << endl;
			return;
		}
	else {
		cout << "id��Ϊ������" << endl;
		return;
	}



	if (choice == "1") {
		student data;
		data.input_id(id);
		data.input_name(name);
		data.input_password(password);
		if (management.duplicate_id(data, management.students) == true) {
			cout << "id�ظ�,���ʧ��" << endl;
			return;
		}
		cout << "��ӳɹ�" << endl;
		management.students.insert({ data.return_id(), data });
		management.save_account(data, project_paths::STUDENT_FILE);
	}
	else if (choice == "2") {
		teacher data;
		data.input_id(id);
		data.input_name(name);
		data.input_password(password);
		if (management.duplicate_id(data, management.teachers) == true) {
			cout << "id�ظ�,���ʧ��" << endl;
			return;
		}
		cout << "��ӳɹ�" << endl;
		management.teachers.insert({ data.return_id(), data });
		management.save_account(data, project_paths::TEACHER_FILE);
	}
	else {
		cout << "����������" << endl;
		return;
	}
}

void administrator::view_account() const {
	cout << "ѧ��" << endl;
	for (auto it = management.students.begin(); it != management.students.end(); it++)
		cout << "id: " << (*it).second.return_id() << "\t����: " << (*it).second.return_password() << "\t����: " << (*it).second.return_name() << endl;
	cout << "��ʦ" << endl;
	for (auto it = management.teachers.begin(); it != management.teachers.end(); it++)
		cout << "id: " << (*it).second.return_id() << "\t����: " << (*it).second.return_password() << "\t����: " << (*it).second.return_name() << endl;
}

//void administrator::check_computer_room() const {
//	cout << "������Ϣ" << endl;
//	for (auto it = management.room.begin(); it != management.room.end(); it++)
//		cout << "����id: " << (*it).second.return_id() << "\t���û�λ: " << (*it).second.return_available() << "\t�������: " << (*it).second.return_capacity() << "\t����: " << (*it).second.return_name() << endl;
//}

void administrator::clear() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	string temp;

	cin >> temp;

	if (temp != "1") {
		cout << "��ȡ����ղ���" << endl;
		return;
	}

	cout << "ȷ��" << endl;
	ofstream print(project_paths::ORDER_FILE, ios::trunc);
	print.close();

	management.appointments.clear();

	cout << "��ճɹ�" << endl;
}

void administrator::erase() {
	string day;
	string period;
	string room_id;
	string status;
	string user_id;

	management.view_all_appointments();

	cout << "��������:" << endl;
	cin >> day;
	cout << "����������" << endl;
	cin >> period;
	cout << "������ѧ��ID" << endl;
	cin >> user_id;
	cout << "���������ID" << endl;
	cin >> room_id;
	cout << "������ԤԼ״̬" << endl;
	cout << "���1/ͨ��2/�ܾ�3/ȡ��4" << endl;
	cin >> status;

	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	if (management.duplicate_key(key) == false) {
		cout << "û�����ԤԼ" << endl;
		return;
	}

	management.appointments.erase(key);
	cout << "ɾ�����" << endl;
}

//void administrator::view_all_appointments() const {
//
//}

//void administrator::logout() {
//
//}

void administrator::menu() const {
	cout << "1,����˺�" << endl
		<< "2,�鿴�˺�" << endl
		<< "3,�鿴����" << endl
		<< "4,���ԤԼ" << endl
		<< "5,�鿴����ԤԼ" << endl
		<< "6,ɾ��ԤԼ" << endl
		<< "7,���ӻ���" << endl
		<< "8,�鿴���л���" << endl
		<< "0,�˳���¼" << endl;
}

//void administrator::login() const {
//
//}

void administrator::input_function() {
	cout << "��ӭ����Ա:" << data_management::current_user->return_name() << "��½" << endl;
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


	cout << "������������:" << endl;
	cin >> id;
	cout << "�������������" << endl;
	cin >> name;
	cout << "����������λ����" << endl;
	cin >> capacity;

	computer_room data;

	available = capacity;
	string str = id + '|' + capacity + '|' + available + '|' + name;
	if (management.parsing_room(str, data) == false) {
		cout << "�����������" << endl;
		return;
	}
	if (management.duplicate_id(data, management.room) == true) {
		cout << "id�ظ�,���ʧ��" << endl;
		return;
	}
	if (management.room_audit(data) == false) {
		cout << "�������ݲ�����" << endl;
		return;
	}

	management.room_audit(data);

	management.room.insert({ data.return_id(),data });
	management.save_room(data, project_paths::ROOM_FILE);
	cout << "��ӳɹ�" << endl;
}

administrator::administrator() {

}

administrator::~administrator() {

}