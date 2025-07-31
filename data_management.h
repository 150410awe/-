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

	// 分身份存储（核心数据）
	map<int32_t, student> students;
	map<int32_t, teacher> teachers;
	map<int32_t, administrator> admins;
	map<int32_t, computer_room> room;
	unordered_map<string, full_appointment> appointments;

	// 统一索引（用于登录）
	//map<int32_t, identity*> users;			// 用户数据存储

	//加载
	void loading();
	//加载身份
	template<typename T>
	void loading_identity(const string& filename, map<int32_t, T>& container);
	//加载机房
	void loading_ROOM_FILE(const string& filename);
	//加载预约
	void loading_ORDER_FILE(const string& filename);
	//是否为纯数字
	bool pure_num(string& str);
	//开始菜单
	void start_menu();
	//登录
	template<typename T>
	void login(map<int32_t, T>& container);

	//输入功能
	//string input_function();

	//退出登录
	void logout();
	//文件是否打开成功,不成功请着删除
	bool opening_file(const string& filename, const fstream& operation);
	//解析机房
	bool parsing_room(const string& line, computer_room& data);
	//审核机房数据
	bool room_audit(computer_room& data);
	//是否有该机房
	bool room_existence(const int32_t id);
	//解析身份
	template<typename T>
	bool resolving_identities(const string& line, T& data);
	//身份错误数据输出
	template<typename T>
	void identities_incorrect_data_output(T& data);
	//解析预约
	bool analysis_reservation(const string& line, full_appointment& data);
	//审核预约数据
	bool review_appointment_data(const full_appointment& data);
	//ID重复,找到为true
	template<typename T>
	bool duplicate_id(T& data, map<int32_t, T>& container);
	//template<typename T>
	//bool duplicate_id(map<int32_t, T>& container , int32_t key);
	
	//生成唯一key
	string generate_appointment_key(const full_appointment& data);
	//key重复
	bool duplicate_key(const string& key);
	string generate_appointment_key(const string& day, const string& periody, const string& user_id, const string& room_id, const string& status);
	//查看所有预约-查看全部预约信息以及预约状态
	void view_all_appointments() const;
	//超出范围
	bool beyond_scope(double id);
	bool full_appointment_beyond_scope(double day,double period,double user_id, double room_id, double status);
	bool room_beyond_scope(double id, double capacity, double available);
	//保存预约
	void save_reservation(full_appointment& data, const string& filename);
	//保存机房
	void save_room(computer_room& data, const string& filename);
	//退出保存
	void exit_save();
	//退出保存身份数据
	template<typename T>
	void exit_identity_save(const string& filename, map<int32_t, T>& container);
	//机房数据
	void exit_room_save();
	//预约
	void exit_reservation_save();
	//查看所有机房
	void view_all_room();
	//添加管理员
	void add_administrator();
	//保存身份
	template<typename T>
	void save_account(T& data, const string& filename);


	data_management();

	~data_management();
};