#pragma once
#include "identity.h"

class administrator : public identity {
public:
	//����˺� ���ѧ�����ʦ���˺ţ���Ҫ���ѧ����Ż��ʦְ�����Ƿ��ظ�
	void add();
	//�鿴�˺� ����ѡ��鿴ѧ�����ʦ��ȫ����Ϣ
	void view_account() const;
	//�鿴���� �鿴���л�������Ϣ
	//void check_computer_room() const;
	//���ԤԼ �������ԤԼ��¼
	void clear();
	//ɾ��ԤԼ ɾ��ԤԼ��¼
	void erase();
	//�鿴����ԤԼ-�鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
	//void view_all_appointments() const override;
	//ע����¼-�˳���¼
	//void logout() override;
	//����Ա�˵�
	void menu() const override;
	//����Ա��¼
	//void login() const override;
	//���빦��
	void input_function() override;
	//�����˺�
	//template<typename T>
	//void save_account(T& data,const string& filename);
	//�û���������˺�ѡ��
	//void input_add();
	
	//���ӻ���
	void add_computer_room();

	administrator();

	~administrator() override;
};