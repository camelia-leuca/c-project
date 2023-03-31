#pragma once
#include "Friendship.h"
class Friendship_validator
{
private:
	int no_errors;
	string message;
public:
	Friendship_validator();
	~Friendship_validator();

	int validate(Friendship& f);
	int get_no_errors();
	string get_message();
};