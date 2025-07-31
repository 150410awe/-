#pragma once
#include "identity.h"

class administrator : public identity {
public:
	//添加账号 添加学生或教师的账号，需要检测学生编号或教师职工号是否重复
	void add();
	//查看账号 可以选择查看学生或教师的全部信息
	void view_account() const;
	//查看机房 查看所有机房的信息
	//void check_computer_room() const;
	//清空预约 清空所有预约记录
	void clear();
	//删除预约 删除预约记录
	void erase();
	//查看所有预约-查看全部预约信息以及预约状态
	//void view_all_appointments() const override;
	//注销登录-退出登录
	//void logout() override;
	//管理员菜单
	void menu() const override;
	//管理员登录
	//void login() const override;
	//输入功能
	void input_function() override;
	//保存账号
	//template<typename T>
	//void save_account(T& data,const string& filename);
	//用户输入添加账号选择
	//void input_add();
	
	//增加机房
	void add_computer_room();

	administrator();

	~administrator() override;
};