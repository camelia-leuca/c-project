#include "User.h"
#include <cstring>
#include "Network.h"

void User::set_id(int id)
{
	this->id = id;
}

User::User()
{
	Network::current_id++;
	this->id = Network::current_id;
	this->username = NULL;
	this->password = NULL;
}

User::User(const char* username, const char* password)
{
	Network::current_id++;
	this->id = Network::current_id;

	if (username == NULL)
		this->username = NULL;
	else
	{
		this->username = new char[strlen(username) + 1];
		strcpy_s(this->username, strlen(username) + 1, username);
	}
	
	if (password == NULL)
		this->password = NULL;
	else
	{
		this->password = new char[strlen(password) + 1];
		strcpy_s(this->password, strlen(password) + 1, password);
	}
}

User::User(const User& u)
{
	this->id = u.id;

	if (u.username == NULL)
		this->username = NULL;
	else
	{
		this->username = new char[strlen(u.username) + 1];
		strcpy_s(this->username, strlen(u.username) + 1, u.username);
	}

	if (u.password == NULL)
		this->password = NULL;
	else
	{
		this->password = new char[strlen(u.password) + 1];
		strcpy_s(this->password, strlen(u.password) + 1, u.password);
	}
}

User::~User()
{
	if (this->username)
		this->username = NULL;

	if (this->password)
		this->password = NULL;
}

int User::get_id()
{
	return this->id;
}

char* User::get_username()
{
	return this->username;
}

char* User::get_password()
{
	return this->password;
}

void User::set_username(const char* username)
{
	if (username == NULL)
		this->username = NULL;
	else
	{
		this->username = new char[strlen(username) + 1];
		strcpy_s(this->username, strlen(username) + 1, username);
	}
}

void User::set_password(const char* password)
{
	if (password == NULL)
		this->password = NULL;
	else
	{
		this->password = new char[strlen(password) + 1];
		strcpy_s(this->password, strlen(password) + 1, password);
	}
}

User& User::operator=(const User& u)
{
	if (this != &u)
	{
		this->set_id(u.id);
		this->set_username(u.username);
		this->set_password(u.password);
	}
	return *this;
}

bool User::operator==(const User& u)
{
	return strcmp(u.username, this->username) == 0 and strcmp(u.password, this->password) == 0;
}

ostream& operator<<(ostream& os, const User& u)
{
	if (u.username and u.password)
		os << "User(id: " << u.id << ", username: " << u.username << ", password: " << u.password << ")";
	return os;
}
