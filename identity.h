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
	* 不加const修饰返回值的原因
	* 基本类型返回值本身就是值拷贝，加const无意义（不影响调用方使用）
	* 不会暴露内部状态的引用/指针，无需保护
	* 现代编译器对基本类型返回值有优化（通常通过寄存器传递）
	* string
	* 必须加const引用的原因：
	* 避免拷贝开销（特别是长字符串）
	* 防止外部修改内部状态（保护封装性）
	* 与const成员函数形成双重保护
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
	* 对于string等复杂类型：
	* 传const引用避免拷贝 节约资源
	* const保证不会意外修改传入参数
	* 对于int等基本类型：
	* 直接传值更高效（引用反而可能增加间接访问开销）
	* 基本类型拷贝代价极低
	* 但是用不上
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