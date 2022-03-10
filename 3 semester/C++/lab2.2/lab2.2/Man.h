#pragma once
#include <string>

class Man
{
private:
	std::string name;
	std::string last_name;
public:
	Man();
	Man(std::string new_last_name, std::string new_name);
	Man(const Man& man);

	std::string get_last_name() const;
	void set_last_name(std::string str);

	std::string get_name() const;
	void set_name(std::string str);

	friend std::ostream& operator<<(std::ostream& out, const Man& man);
};
