#pragma once
#include <cstdint>
#include <string>

#define EMPTY -1

using namespace std;

class identity {
private:
	int32_t id = EMPTY;
	std::string password;
	std::string name;
public:

	/*
	* int32_t
	* ����const���η���ֵ��ԭ��
	* �������ͷ���ֵ�������ֵ��������const�����壨��Ӱ����÷�ʹ�ã�
	* ���ᱩ¶�ڲ�״̬������/ָ�룬���豣��
	* �ִ��������Ի������ͷ���ֵ���Ż���ͨ��ͨ���Ĵ������ݣ�
	* string
	* �����const���õ�ԭ��
	* ���⿽���������ر��ǳ��ַ�����
	* ��ֹ�ⲿ�޸��ڲ�״̬��������װ�ԣ�
	* ��const��Ա�����γ�˫�ر���
	*/

	int32_t return_id() const {
		return id;
	}
	const std::string& return_password() const {
		return password;
	}
	const std::string& return_name() const {
		return name;
	}

	/*
	* ����string�ȸ������ͣ�
	* ��const���ñ��⿽�� ��Լ��Դ
	* const��֤���������޸Ĵ������
	* ����int�Ȼ������ͣ�
	* ֱ�Ӵ�ֵ����Ч�����÷����������Ӽ�ӷ��ʿ�����
	* �������Ϳ������ۼ���
	* �����ò���
	*/

	void input_id(int32_t id) {
		this->id = id;
	}
	void input_name(const std::string name) {
		this->name = name;
	}
	void input_password(const std::string password) {
		this->password = password;
	}


	virtual void menu() const = 0;

	//virtual void view_all_appointments() const = 0;

	//virtual void logout() = 0;

	virtual void input_function() = 0;

	identity() = default;

	virtual ~identity() = default;
};