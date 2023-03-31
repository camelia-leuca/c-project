#include "User_service.h"
#include "Exception.h"

User_service::User_service(User_repo&user_repo, User_validator& user_validator):user_repo(user_repo), user_validator(user_validator)
{ 
}

User_service::~User_service()
{
}

vector<User*> User_service::get_all_users()
{
	return this->user_repo.get_all_users();
}

void User_service::add_user(const char* username, const char* password)
{
	User user = User(username, password);
	if (this->user_validator.validate(user) == 0)
		this->user_repo.add_user(user);
	else
		throw Validation_exception(user_validator.get_message());
}

void User_service::update_user(const char* username, const char* password, const char* updated_username, const char* updated_password)
{
	User updated_user(updated_username, updated_password);
	User user(username, password);
	if (this->user_validator.validate(updated_user) == 0)
		this->user_repo.update_user(user, updated_user);
	else
		throw Validation_exception(user_validator.get_message());
}

void User_service::delete_user(const char* username, const char* password)
{
	User user = User(username, password);
	this->user_repo.delete_user(user);
}

bool User_service::user_exists(const char* username, const char* password)
{
	User user = User(username, password);
	return this->user_repo.user_exists(user);
}

bool User_service::user_exists(const char* username)
{
	if (username == NULL)
		return false;
	vector<User*> users = this->user_repo.get_all_users();
	for (int i = 0; i < users.size(); i++)
	{
		if (strcmp(users[i]->get_username(), username) == 0)
		{
			return true;
		}
	}
	return false;
}

User& User_service::get_user_by_username(const char* username)
{
	vector<User*> users = this->user_repo.get_all_users();
	for (int i=0;i<users.size();i++)
	{
		if (strcmp(users[i]->get_username(), username) == 0)
		{
			return *users[i];
		}
	}
}
