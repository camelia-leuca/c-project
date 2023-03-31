#pragma once
#include"List.h"
#include"User.h"
#include "User_repo.h"
#include "User_validator.h"
class User_service
{
private:
	User_repo& user_repo;
	User_validator& user_validator;
public:
	User_service(User_repo& user_repo, User_validator& user_validator);
	~User_service();

	vector<User*> get_all_users();

	void add_user(const char* username, const char* password);
	void update_user(const char* username, const char* password, const char* updated_username, const char* updated_password);
	void delete_user(const char* username, const char* password);

	bool user_exists(const char* username, const char* password);
	bool user_exists(const char* username);

	User&get_user_by_username(const char* username);
};