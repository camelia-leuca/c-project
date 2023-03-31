#pragma once
#include "User.h"
class User_validator
{
private:
	int no_errors;
	string message;
public:
	User_validator();
	~User_validator();

	int validate(User& u);
	int get_no_errors();
	string get_message();
};