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
	string status = "1";//Ĭ�ϴ����

	management.view_all_appointments();

	cout << "��������:" << endl;
	cin >> day;
	cout << "����������" << endl;
	cin >> period;
	cout << "���������ID" << endl;
	cin >> room_id;


	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	if (management.duplicate_key(key) == true) {
		cout << "�����ԤԼ,����ʧ��" << endl;
		return;
	}

	full_appointment data;

	if (management.analysis_reservation(key, data) == false) {
		cout << "ԤԼ�������" << endl;
		return;
	}
	if (management.room_existence(stoi(room_id)) == false) {
		cout << "�����������" << endl;
		return;
	}
	if (management.review_appointment_data(data) == false) {
		cout << "ԤԼ���ݲ�����" << endl;
		return;
	}

	management.appointments.insert({ key, data });
	management.save_reservation(data, project_paths::ORDER_FILE);
	cout << "����ɹ�" << endl;
}

void student::look_yourself() const {
	int32_t id = management.current_user->return_id();

	cout << "�ҵ�ԤԼ" << endl;

	for (auto it = management.appointments.begin(); it != management.appointments.end(); it++)
		if ((*it).second.return_user_id() == id)
			cout << "��: " << (*it).second.return_day()
			<< "\t����: " << (*it).second.return_periody()
			<< "\tԤԼ�û�ID�� " << (*it).second.return_user_id()
			<< "\t����ID: " << (*it).second.return_room_id()
			<< "\tԤԼ״̬: " << (*it).second.return_status() << endl;
}

//void student::view_all_appointments() const {
//
//}

void student::cancel() {
	cout << "������ԤԼ��Ϣ" << endl;

	string day;
	string period;
	string room_id;
	string user_id = to_string(data_management::current_user->return_id());
	string status;

	look_yourself();

	cout << "��������:" << endl;
	cin >> day;
	cout << "����������" << endl;
	cin >> period;
	cout << "���������ID" << endl;
	cin >> room_id;
	cout << "������ԤԼ״̬�����1/ͨ��2" << endl;	
	cin >> status;
	if (status != "1" && status != "2") {
		cout << "ԤԼ״̬����" << endl;
		return;
	}

	string key = management.generate_appointment_key(day, period, user_id, room_id, status);

	full_appointment data;

	if (management.duplicate_key(key) == false) {
		cout << "û�����ԤԼ,ȡ��ʧ��" << endl;
		return;
	}
	//add�ͼ���ʱ��֤��key����ȷ�����Բ��÷����Ա����;
	management.appointments.erase(key);
	//��дһ��̫�鷳��,��save_reservation,��Ҫ���Ҳ���;
	status = "4";
	key = management.generate_appointment_key(day, period, user_id, room_id, status);//Ϊ�˷�ֹ������������,�������¸�ֵ
	management.analysis_reservation(key, data);
	management.appointments.insert({ key, data });
	management.save_reservation(data, project_paths::ORDER_FILE);
	cout << "ȡ���ɹ�" << endl;
}

//void student::logout() {
//
//}

void student::menu() const {
	cout << "1,����ԤԼ" << endl
		<< "2,�鿴�ҵ�ԤԼ" << endl
		<< "3,�鿴����ԤԼ" << endl
		<< "4,ȡ��ԤԼ" << endl
		<< "5,�鿴���л���" << endl
		<< "0,�˳���¼" << endl;
}

//void student::login() const{
//
//}

void student::input_function() {
	cout << "��ӭѧ��:" << data_management::current_user->return_name() << "��½" << endl;
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