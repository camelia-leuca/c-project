#pragma once
#include "User.h"
#include "List.h"
class User_repo
{
private:
	List<User>*& user_list;
public:
	User_repo(List<User>*& user_list);
	~User_repo();

	vector<User*> get_all_users();

	void add_user(const User&user);
	void update_user(const User& user, const User& updated_user);
	void delete_user(const User& user);
	bool user_exists(const User& user);
};