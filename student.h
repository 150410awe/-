#pragma once
#include"identity.h"
#include "full_appointment.h"

class student : public identity {
public:
	//����ԤԼ-ԤԼ����
	void application();
	//�鿴�����ԤԼ-�鿴�Լ���ԤԼ״̬
	void look_yourself() const;
	//ȡ��ԤԼ-ȡ�������ԤԼ��ԤԼ�ɹ�������е�ԤԼ����ȡ�� 
	void cancel();
	//�鿴����ԤԼ-�鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
	//void view_all_appointments() const override;
	//ע����¼-�˳���¼
	//void logout() override;
	//ѧ���˵�
	void menu() const override;
	//ѧ����¼
	//void login() const override;
	//���빦��
	void input_function() override;

	student();

	~student() override;
};