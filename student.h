#pragma once
#include"identity.h"
#include "full_appointment.h"

class student : public identity {
public:
	//申请预约-预约机房
	void application();
	//查看自身的预约-查看自己的预约状态
	void look_yourself() const;
	//取消预约-取消自身的预约，预约成功或审核中的预约均可取消 
	void cancel();
	//查看所有预约-查看全部预约信息以及预约状态
	//void view_all_appointments() const override;
	//注销登录-退出登录
	//void logout() override;
	//学生菜单
	void menu() const override;
	//学生登录
	//void login() const override;
	//输入功能
	void input_function() override;

	student();

	~student() override;
};