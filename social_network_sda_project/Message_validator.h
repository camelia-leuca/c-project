#pragma once
#include "Message.h"
class Message_validator
{
private:
	int no_errors;
	string message;
public:
	Message_validator();
	~Message_validator();

	int validate(Message& m);
	int get_no_errors();
	string get_message();
};