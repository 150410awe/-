#pragma once
#include "identity.h"

class teacher : public identity{
public:
	//审核预约
	void audit();
	//查看所有预约-查看全部预约信息以及预约状态
	//void view_all_appointments() const override;
	//注销登录-退出登录
	//void logout();
	//老师菜单
	void menu() const override;
	//老师登录
	//void login() const override;
	//输入功能
	void input_function() override;

	teacher();

	~teacher() override;
};