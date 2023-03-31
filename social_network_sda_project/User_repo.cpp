#include "User_repo.h"

User_repo::User_repo(List<User>*& user_list):user_list(user_list)
{
}

User_repo::~User_repo()
{
}

vector<User*> User_repo::get_all_users()
{
	return this->user_list->get_all();
}

void User_repo::add_user(const User& user)
{
	this->user_list->add(user);
}

void User_repo::update_user(const User& user, const User& updated_user)
{
	this->user_list->update(user, updated_user);
}

void User_repo::delete_user(const User& user)
{
	this->user_list->remove(user);
}

bool User_repo::user_exists(const User& user)
{
	if (this->user_list->exists(user))
		return true;

	return false;
}
