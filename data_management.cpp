#include "data_management.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <cstdio>
#include <limits>

using namespace std;

identity* data_management::current_user = nullptr;

void data_management::loading() {
	loading_identity(project_paths::STUDENT_FILE, students);
	loading_identity(project_paths::TEACHER_FILE, teachers);
	loading_identity(project_paths::ADMIN_FILE, admins);
	loading_ROOM_FILE(project_paths::ROOM_FILE);
	loading_ORDER_FILE(project_paths::ORDER_FILE);
}

/*
* ��ʽʵ����ģ�岻�߱�ͨ����,û����
*/
template void data_management::loading_identity<student>(const string&, map<int32_t, student>&);
template void data_management::loading_identity<teacher>(const string&, map<int32_t, teacher>&);
template void data_management::loading_identity<administrator>(const string&, map<int32_t, administrator>&);
template<typename T>
void data_management::loading_identity(const string& filename, map<int32_t, T>& container) {
	fstream input(filename, ios::in);

	if (opening_file(filename, input) == false)
		return;
	//cout << "�ļ��򿪳ɹ�" << endl;

	string line;
	int32_t num = 0;
	while (getline(input, line)) {
		//getline()
		num++;

		T data;

		if (resolving_identities(line, data) == false) {
			identities_incorrect_data_output(data);
			cout << "�������ļ�" << filename << "��" << num << "��" << endl;
			continue;
		}

		//cout << "id: " << id << "\tpassword: " << password << "\tname: " << name << endl;
		if (duplicate_id(data, container) == true) {
			cout << "���ļ�" << filename << "��" << num << "��" << endl;
			cout << "ID�����ظ�,name: " << data.return_name() << "�����ظ��û�����" << endl;
			continue;
		}
		container.insert({ data.return_id(),data });
	}

	for (auto it = container.begin(); it != container.end(); it++)
		cout << (*it).first << " " << (*it).second.return_name() << " " << (*it).second.return_password() << endl;
}

void data_management::loading_ROOM_FILE(const string& filename) {
	fstream input(filename, ios::in);

	if (opening_file(filename, input) == false)
		return;


	string line;

	int32_t num = 0;
	while (getline(input, line)) {
		//getline()
		num++;

		computer_room data;

		if (parsing_room(line, data) == false) {
			cout << "�������ݴ���,���ļ�" << filename << "��" << num << "��" << endl;
			continue;
		}

		if (room_audit(data) == false) {
			cout << "�������ݲ�����,���ļ�" << filename << "��" << num << "��" << endl;
			continue;
		}

		if (duplicate_id(data, room) == true) {
			cout << "���ļ�" << filename << "��" << num << "��" << endl;
			cout << "ID�����ظ�,name: " << data.return_name() << "�����ظû�������" << endl;
			continue;
		}

  		//cout << "id: " << id << "\tcapacity: " << capacity << "\tavailable: " << available << "\tname: " << name << endl;

		room.insert({ data.return_id(), data});
	}

	for (auto it = room.begin(); it != room.end(); it++)
		cout << (*it).first << " " << (*it).second.return_capacity() << " " << (*it).second.return_available() << " " << (*it).second.return_name() << endl;
}

void data_management::loading_ORDER_FILE(const string& filename) {
	fstream input(filename, ios::in);
	

	if (opening_file(filename, input) == false)
		return;

	string line;
	int32_t num = 0;

	full_appointment data;

	while (getline(input, line)) {

		num++;

		if (analysis_reservation(line, data) == false) {
			cout << "ԤԼ���ݴ���,���ļ�" << filename << "��" << num << "��" << endl;
			continue;
		}

		if (review_appointment_data(data) == false) {
			cout << "ԤԼ���ݲ�����,���ļ�" << filename << "��" << num << "��" << endl;
			continue;
		}

		string key = generate_appointment_key(data);

		if (duplicate_key(key) == true) {
			cout << "�ļ�" << filename << "��" << num << "��,���ظ���ԤԼ" << endl;
			continue;
		}

		appointments.insert({ key , data });

		//cout << data.return_day() << " " << data.return_periody() << endl;
		//time.push_back(,data);
	}

	for (auto it = appointments.begin(); it != appointments.end(); it++)
		cout << (*it).second.return_day() << " " << (*it).second.return_periody() << " " << (*it).second.return_user_id() << " " << (*it).second.return_room_id() << " " << (*it).second.return_status() << endl;
}

bool data_management::pure_num(string& str) {
	for (uint8_t ch : str)
		if (isdigit(ch) == false)
			return false;
	return true;
}

void data_management::start_menu() {
	cout << "�������������" << endl
		<< "1,ѧ������" << endl
		<< "2,��ʦ" << endl
		<< "3,����Ա" << endl
		<< "4,��ӹ���Ա" << endl
		<< "0,�� ��" << endl
		<< "��������ѡ��:" << endl;
}

template void data_management::login<student>(map<int32_t, student>&);
template void data_management::login<teacher>(map<int32_t, teacher>&);
template void data_management::login<administrator>(map<int32_t, administrator>&);
template<typename T>
void data_management::login(map<int32_t, T>& container) {

	for (auto it = container.begin(); it != container.end(); it++)
		cout << (*it).first << " " << (*it).second.return_name() << " " << (*it).second.return_password() << endl;

	string s_id;
	int32_t id = 0;
	string name;
	string password;
	while (true) {
		cout << "����:�˳� �˳�" << endl;
		cout << "������ID��" << endl;
		cin >> s_id;

		if (s_id == "�˳�") {
			cout << "�˳�" << endl;
 			current_user = nullptr;		//������nullptr;
			return;
		}

		if (pure_num(s_id) == false) {
			cout << "id�������" << endl;
			continue;
		}
		else 
			id = stoi(s_id);
		
		//���غ�ħ��,��Ҳ���ǵ���ɶ
		if (cin.rdbuf()->in_avail() > 0)   // �������ǿ�ʱ�� ignore
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "����������" << endl;
		getline(cin, name);
		//���غ�ħ��,��Ҳ���ǵ���ɶ
		if (cin.rdbuf()->in_avail() > 0)   // �������ǿ�ʱ�� ignore
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "����������" << endl;
		getline(cin, password);
		//���غ�ħ��,��Ҳ���ǵ���ɶ
		if (cin.rdbuf()->in_avail() > 0)   // �������ǿ�ʱ�� ignore
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		auto pos = container.find(id);		//��Ϊid���ظ�ʵ����ֻ��id�Ϳ�����

		if (pos == container.end()) {
			cout << "id����" << endl;
			continue;
		}
		if ((*pos).second.return_name() != name) {
			cout << "���ִ���" << endl;
			continue;
		}
		if ((*pos).second.return_password() != password) {
			cout << "�������" << endl;
			continue;
		}
		cout << "������ȷ" << endl;
		current_user = new T;
		current_user->input_id(id);
		current_user->input_name(name);
		current_user->input_password(password);
		break;
	}
	//current_user->menu();
	current_user->input_function();
	logout();
}

void data_management::logout() {
	if (current_user != nullptr)
		delete current_user;
	current_user = nullptr;
	cout << "�˳��ɹ�" << endl;
	cout << "�ص���¼�˵�" << endl;
}

//string data_management::input_function() {
//	string choice;
//	while (cin >> choice) {
//
//	}
//}

bool data_management::opening_file(const string& filename, const fstream& operation) {
	if (operation.is_open() == false) {
		cout << "�ļ���ʧ��,�ļ���" << filename << ",ɾ���ļ�" << endl;
		if (remove(filename.c_str()) == false)
			cout << "�ļ�ɾ���ɹ�" << endl;
		else
			cout << "�ļ�ɾ��ʧ��(���ܲ����ڣ�" << endl;
		cout << "��ֹ�ļ���ȡ����,�˳�" << endl;
		return false;
	}
	return true;
}

template bool data_management::resolving_identities<student>(const string&, student&);
template bool data_management::resolving_identities<teacher>(const string&, teacher&);
template bool data_management::resolving_identities<administrator>(const string&, administrator&);
template<typename T>
bool data_management::resolving_identities(const string& line, T& data) {

	string s_id;
	string password;
	string name;

	istringstream iss(line);

	if (getline(iss, s_id, '|') && pure_num(s_id) == true && getline(iss, password, '|') && getline(iss, name)) {

		double id = stod(s_id);

		if (beyond_scope(id) == true) {
			cout << "�û���������̫��" << endl;
			return false;
		}

		data.input_id(id);
		data.input_password(password);
		data.input_name(name);
		return true;
	}
	else
		return false;
}

template void data_management::identities_incorrect_data_output<student>(student&);
template void data_management::identities_incorrect_data_output<teacher>(teacher&);
template void data_management::identities_incorrect_data_output<administrator>(administrator&);
template<typename T>
void data_management::identities_incorrect_data_output(T& data) {
	cout << "��Ч�û�����:" << "ID: " << data.return_id()
		<< " ����: " << data.return_name()
		<< " ����: " << data.return_password() << endl;
	cout << "�����ظ��û�����" << endl;
}

bool data_management::parsing_room(const string& line, computer_room& data) {
	//int32_t id = EMPTY;
	//int32_t capacity = EMPTY;
	//int32_t available = EMPTY;
	string s_id;
	string s_capacity;
	string s_available;
	string name;

	istringstream iss(line);


	if (getline(iss, s_id, '|') && pure_num(s_id) == true && 
		getline(iss, s_capacity, '|') && pure_num(s_capacity) == true && 
		getline(iss, s_available, '|') && pure_num(s_available) == true && 
		getline(iss, name, '|')) {
		
		double id = stod(s_id);
		double capacity = stod(s_capacity);
		double available = stod(s_available);
		if (room_beyond_scope(id, capacity, available) == true) {
			cout << "������������̫��" << endl;
			return false;
		}
		
		data.input_id(id);
		data.input_capacity(capacity);
		data.input_available(available);
		data.input_name(name);
		return true;
	}
	else 
		return false;
}

bool data_management::room_audit(computer_room& data) {
	if (data.return_id() == EMPTY || data.return_capacity() == EMPTY || data.return_available() == EMPTY || data.return_name().empty() == true || data.return_capacity() <= 0 || data.return_available() < 0 || data.return_capacity() < data.return_available()) {
		cout << "��Ч��������: ID: " << data.return_id()
			<< " ����: " << data.return_capacity()
			<< " ����: " << data.return_available() 
			<< " ����: " << data.return_name() << endl;
		cout << "�����ظû�������" << endl;
		return false;
	}
	return true;
}


template bool data_management::duplicate_id<computer_room>(computer_room&, map<int32_t, computer_room>&);
template bool data_management::duplicate_id<student>(student&, map<int32_t, student>&);
template bool data_management::duplicate_id<teacher>(teacher&, map<int32_t, teacher>&);
template bool data_management::duplicate_id<administrator>(administrator&, map<int32_t, administrator>&);
template<typename T>
bool data_management::duplicate_id(T& data, map<int32_t, T>& container) {
	return container.find(data.return_id()) != container.end();
}


bool data_management::analysis_reservation(const string& line, full_appointment& data) {
	string s_day;
	string s_period;
	string s_user_id;
	string s_room_id;
	string s_status;
	int32_t period = EMPTY;
	int32_t day = EMPTY;
	int32_t user_id = EMPTY;
	int32_t room_id = EMPTY;
	int32_t status = EMPTY;

	istringstream iss(line);

	if (getline(iss, s_day, '|') && pure_num(s_day) && 
		getline(iss, s_period, '|') && pure_num(s_period) &&
		getline(iss,s_user_id,'|') && pure_num(s_user_id) && 
		getline(iss, s_room_id, '|') && pure_num(s_room_id)&& 
		getline(iss, s_status) && pure_num(s_status)) {

		double day = stod(s_day);
		double period = stod(s_period);
		double user_id = stod(s_user_id);
		double room_id = stod(s_room_id);
		double status = stod(s_status);

		if (full_appointment_beyond_scope(day, period, user_id, room_id, status) == true) {
			cout << "ѧ��ԤԼ����̫��" << endl;
			return false;
		}

		data.input_day(stoi(s_day));
		data.input_period(stoi(s_period));
		data.input_user_id(stoi(s_user_id));
		data.input_room_id(stoi(s_room_id));
		data.input_status(stoi(s_status));

		return true;
	}
	//cout << s_day << " " << s_period << endl;
	return false;
}

bool data_management::review_appointment_data(const full_appointment& data) {
	if (data.return_day() <= 0 || data.return_day() > 7)		//0<day<=7
		return false;
	if (data.return_periody() > 2 || data.return_periody() <= 0)//1<=periody<=2
		return false;
	if (data.return_status() < 1 || data.return_status() > 4)	//1<=status<=4
		return false;
	return true;
}

string data_management::generate_appointment_key(const full_appointment& data) {
	return to_string(data.return_day()) + '|'
		+ to_string(data.return_periody()) + '|'
		+ to_string(data.return_user_id()) + '|'
		+ to_string(data.return_room_id()) + '|'
		+ to_string(data.return_status());
}
string data_management::generate_appointment_key(const string& day, const string& periody, const string& user_id, const string& room_id, const string& status) {
	return day + '|'
		+ periody + '|'
		+ user_id + '|'
		+ room_id + '|'
		+ status;
}

bool data_management::duplicate_key(const string& key) {
	return appointments.find(key) != appointments.end();
}

void data_management::view_all_appointments() const {
	cout << "�鿴����ԤԼ" << endl;
	cout << "����(����:1,����:2),ԤԼ״̬�������1/ͨ��2/�ܾ�3/ȡ��4��" << endl;
	for (auto it = appointments.begin(); it != appointments.end(); it++)
		cout << "��: " << (*it).second.return_day() 
		<< "\t����: " << (*it).second.return_periody() 
		<< "\tԤԼ�û�ID�� " << (*it).second.return_user_id() 
		<< "\t����ID: " << (*it).second.return_room_id() 
		<< "\tԤԼ״̬: " << (*it).second.return_status() << endl;
}

bool data_management::room_existence(const int32_t id) {
	for (auto it = room.begin(); it != room.end(); it++)
		if ((*it).second.return_id() == id)
			return true;
	return false;
}

bool data_management::beyond_scope(double id) {
	if (id > INT32_MAX || id < INT32_MIN)
		return true;
	return false;
}
bool data_management::full_appointment_beyond_scope(double day, double period, double user_id, double room_id, double status) {
	if (day > INT32_MAX || day < INT32_MIN ||
		period > INT32_MAX || period < INT32_MIN ||
		user_id > INT32_MAX || user_id < INT32_MIN ||
		room_id > INT32_MAX || room_id < INT32_MIN || 
		status > INT32_MAX || status < INT32_MIN)
		return true;
	return false;
}
bool data_management::room_beyond_scope(double id, double capacity, double available) {
	if (id > INT32_MAX || id < INT32_MIN || 
		capacity > INT32_MAX || capacity < INT32_MIN ||
		available > INT32_MAX || available < INT32_MIN)
		return true;
	return false;
}


void data_management::save_reservation(full_appointment& data, const string& filename) {
	fstream print(filename, ios::out | ios::app);

	if (management.opening_file(filename, print) == false)
		return;

	print << data.return_day() << '|'
		<< data.return_periody() << '|'
		<< data.return_user_id() << '|'
		<< data.return_room_id() << '|'
		<< data.return_status() << endl;
}

void data_management::save_room(computer_room& data, const string& filename) {
	fstream print(filename, ios::out | ios::app);

	if (management.opening_file(filename, print) == false)
		return;

	print << data.return_id() << '|'
		<< data.return_capacity() << '|'
		<< data.return_available() << '|'
		<< data.return_name() << endl;
}

void data_management::exit_save() {
	fstream print_student(project_paths::STUDENT_FILE, ios::out | ios::trunc);
	fstream print_teacher(project_paths::TEACHER_FILE, ios::out | ios::trunc);
	fstream print_administrator(project_paths::ADMIN_FILE, ios::out | ios::trunc);
	fstream print_room(project_paths::ROOM_FILE, ios::out | ios::trunc);
	fstream print_full_appointment(project_paths::ORDER_FILE, ios::out | ios::trunc);

	if (opening_file(project_paths::STUDENT_FILE, print_student) == false)
		print_student.close();
	else
		exit_identity_save(project_paths::STUDENT_FILE, students);

	if (opening_file(project_paths::TEACHER_FILE, print_teacher) == false)
		print_teacher.close();
	else
		exit_identity_save(project_paths::TEACHER_FILE, teachers);

	if (opening_file(project_paths::ADMIN_FILE, print_administrator) == false)
		print_administrator.close();
	else
		exit_identity_save(project_paths::ADMIN_FILE, admins);

	if (opening_file(project_paths::ROOM_FILE, print_room) == false)
		print_room.close();
	else
		exit_room_save();

	if (opening_file(project_paths::ORDER_FILE, print_full_appointment) == false)
		print_full_appointment.close();
	else
		exit_reservation_save();
}

template void data_management::exit_identity_save<student>(const string&, map<int32_t, student>&);
template void data_management::exit_identity_save<teacher>(const string&, map<int32_t, teacher>&);
template void data_management::exit_identity_save<administrator>(const string&, map<int32_t, administrator>&);
template<typename T>
void data_management::exit_identity_save(const string& filename, map<int32_t, T>& container) {
	fstream print(filename, ios::out);

	for (auto index = container.begin(); index != container.end(); index++)
		print << (*index).second.return_id() << "|"
			<< (*index).second.return_password() << "|"
			<< (*index).second.return_name() << endl;
}


template void data_management::save_account<teacher>(teacher&, const string&);
template void data_management::save_account<student>(student&, const string&);
template void data_management::save_account<administrator>(administrator&, const string&);
template<typename T>
void data_management::save_account(T& data, const string& filename){
	fstream print(filename, ios::out | ios::app);

	if (management.opening_file(filename, print) == false)
		return;

	print << data.return_id() << "|"
		<< data.return_password() << "|"
		<< data.return_name() << endl;
}


void data_management::exit_room_save() {
	fstream print(project_paths::ROOM_FILE, ios::out);

	for (auto index = room.begin(); index != room.end(); index++)
		print << (*index).second.return_id() << "|"
		<< (*index).second.return_capacity() << "|"
		<< (*index).second.return_available() << '|'
		<< (*index).second.return_name() << endl;
}

void data_management::exit_reservation_save() {
	fstream print(project_paths::ORDER_FILE, ios::out);

	for (auto index = appointments.begin(); index != appointments.end(); index++)
		print << (*index).second.return_day() << "|"
		<< (*index).second.return_periody() << "|"
		<< (*index).second.return_user_id() << '|'
		<< (*index).second.return_room_id() << '|'
		<< (*index).second.return_status() << endl;
}

void data_management::view_all_room() {
	for (auto index = room.begin(); index != room.end(); index++)
		cout << "�������:" << (*index).second.return_id() 
		<< "\t��������:" << (*index).second.return_name() 
		<< "\t�������:" << (*index).second.return_capacity() << endl;
}

void data_management::add_administrator() {

	string s_id;
	double id = EMPTY;
	string name;
	string password;

	cout << "������id" << endl;
	cin >> s_id;
	cout << "����������" << endl;
	cin >> password;
	cout << "����������" << endl;
	cin >> name;

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


	administrator data;
	data.input_id(id);
	data.input_name(name);
	data.input_password(password);
	if (management.duplicate_id(data, management.admins) == true) {
		cout << "id�ظ�,���ʧ��" << endl;
		return;
	}

	cout << "��ӳɹ�" << endl;
	management.admins.insert({ data.return_id(), data });
	management.save_account(data, project_paths::STUDENT_FILE);

	return;
}

data_management::data_management() {
	loading();
}

data_management::~data_management() {

}