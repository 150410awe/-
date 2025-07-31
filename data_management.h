#pragma once
#include "identity.h"
#include "config.h"
#include "administrator.h"
#include "student.h"
#include "teacher.h"
#include "computer_room.h"
#include "full_appointment.h"
#include <map>
#include <unordered_map>
//#include "make_appointment.h"


using namespace std;

class data_management;

extern data_management management;

class data_management {
public:
	static identity* current_user;

	// ����ݴ洢���������ݣ�
	map<int32_t, student> students;
	map<int32_t, teacher> teachers;
	map<int32_t, administrator> admins;
	map<int32_t, computer_room> room;
	unordered_map<string, full_appointment> appointments;

	// ͳһ���������ڵ�¼��
	//map<int32_t, identity*> users;			// �û����ݴ洢

	//����
	void loading();
	//�������
	template<typename T>
	void loading_identity(const string& filename, map<int32_t, T>& container);
	//���ػ���
	void loading_ROOM_FILE(const string& filename);
	//����ԤԼ
	void loading_ORDER_FILE(const string& filename);
	//�Ƿ�Ϊ������
	bool pure_num(string& str);
	//��ʼ�˵�
	void start_menu();
	//��¼
	template<typename T>
	void login(map<int32_t, T>& container);

	//���빦��
	//string input_function();

	//�˳���¼
	void logout();
	//�ļ��Ƿ�򿪳ɹ�,���ɹ�����ɾ��
	bool opening_file(const string& filename, const fstream& operation);
	//��������
	bool parsing_room(const string& line, computer_room& data);
	//��˻�������
	bool room_audit(computer_room& data);
	//�Ƿ��иû���
	bool room_existence(const int32_t id);
	//�������
	template<typename T>
	bool resolving_identities(const string& line, T& data);
	//��ݴ����������
	template<typename T>
	void identities_incorrect_data_output(T& data);
	//����ԤԼ
	bool analysis_reservation(const string& line, full_appointment& data);
	//���ԤԼ����
	bool review_appointment_data(const full_appointment& data);
	//ID�ظ�,�ҵ�Ϊtrue
	template<typename T>
	bool duplicate_id(T& data, map<int32_t, T>& container);
	//template<typename T>
	//bool duplicate_id(map<int32_t, T>& container , int32_t key);
	
	//����Ψһkey
	string generate_appointment_key(const full_appointment& data);
	//key�ظ�
	bool duplicate_key(const string& key);
	string generate_appointment_key(const string& day, const string& periody, const string& user_id, const string& room_id, const string& status);
	//�鿴����ԤԼ-�鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
	void view_all_appointments() const;
	//������Χ
	bool beyond_scope(double id);
	bool full_appointment_beyond_scope(double day,double period,double user_id, double room_id, double status);
	bool room_beyond_scope(double id, double capacity, double available);
	//����ԤԼ
	void save_reservation(full_appointment& data, const string& filename);
	//�������
	void save_room(computer_room& data, const string& filename);
	//�˳�����
	void exit_save();
	//�˳������������
	template<typename T>
	void exit_identity_save(const string& filename, map<int32_t, T>& container);
	//��������
	void exit_room_save();
	//ԤԼ
	void exit_reservation_save();
	//�鿴���л���
	void view_all_room();
	//��ӹ���Ա
	void add_administrator();
	//�������
	template<typename T>
	void save_account(T& data, const string& filename);


	data_management();

	~data_management();
};