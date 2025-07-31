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
	string status = "1";//�����

	cout << "��������:" << endl;
	cin >> day;
	cout << "����������" << endl;
	cin >> period;
	cout << "������ѧ��id" << endl;
	cin >> user_id;
	cout << "���������ID" << endl;
	cin >> room_id;


	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	full_appointment data;
	cout << key << endl;
	if (management.duplicate_key(key) == false) {
		cout << "û�����ԤԼ,���ʧ��" << endl;
		return;
	}

	cout << "ͨ��2 or �ܾ�3" << endl;
	string choice;
	cin >> choice;
	if (choice != "2" && choice != "3") {
		cout << "ѡ�����" << endl;
		return;
	}

	management.appointments.erase(key);

	status = choice;

	key = management.generate_appointment_key(day, period, user_id, room_id, status);
	management.analysis_reservation(key, data);
	management.appointments.insert({ key, data });
	management.save_reservation(data, project_paths::ORDER_FILE);
	cout << "��˳ɹ�" << endl;
}

//void teacher::view_all_appointments() const {
//
//}

//void teacher::logout() {
//
//}

void teacher::menu() const {
	cout << "1,���ԤԼ" << endl
		<< "2,�鿴����ԤԼ" << endl
		<< "3,�鿴���л���" << endl
		<< "0,�˳���¼" << endl;
}

//void teacher::login() const {
//
//}


void teacher::input_function() {
	cout << "��ӭѧ��:" << data_management::current_user->return_name() << "��½" << endl;
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