#pragma once
#include "identity.h"

class teacher : public identity{
public:
	//���ԤԼ
	void audit();
	//�鿴����ԤԼ-�鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
	//void view_all_appointments() const override;
	//ע����¼-�˳���¼
	//void logout();
	//��ʦ�˵�
	void menu() const override;
	//��ʦ��¼
	//void login() const override;
	//���빦��
	void input_function() override;

	teacher();

	~teacher() override;
};