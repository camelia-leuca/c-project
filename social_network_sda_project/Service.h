#pragma once
#include "List.h"
#include "User.h"
class User_service
{
private:
	List<User>*& list;
public:
	User_service(List<User>*& list);
	~User_service();

	void add_user(const char* username, const char* password);
	void update_user(const char* username, const char* password, const char* updated_username, const char* updated_password);
	void delete_user(const char* username, const char* password);

	bool find_user(const char* username, const char* password);
};