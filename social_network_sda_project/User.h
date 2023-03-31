#pragma once
#include<ostream>
using namespace std;
class User
{
private:
	int id;
	char* username;
	char* password;

	void set_id(int id);
public:

	User();
	User(const char* username, const char* password);
	User(const User& u);

	~User();

	int get_id();
	char* get_username();
	char* get_password();

	void set_username(const char* username);
	void set_password(const char* password);

	User& operator=(const User& u);
	bool operator==(const User& u);

	friend ostream& operator<<(ostream& os, const User& u);
};
